#include "Connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket();
    _error = false;
}


void Connection::connect(QString host, int port) {
    _socket->connectToHost(host, port);

    writeToServer("MODE", QVector<QString>("RUNNING"));

    QObject::connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readFromServer()));
    QObject::connect(_socket, SIGNAL(connected()), this, SLOT(onConnect()));
}

void Connection::connectAndSend(QString host, int port, QFile* file) {
    _socket->connectToHost(host, port);
    writeToServer("MODE", QVector<QString>("FROMFILE"));

    if (!file->open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return;
    }

    // Read file and convert to Json
    QByteArray saveData = file->readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));


    // Read size and write to server
    QVector<QString> sizeParams;
    int size = loadDoc["size"].toInt();
    sizeParams.append(QString::number(size));
    _size = size;

    writeToServer("SIZE", sizeParams);


    // Read robots and write to server
    QVector<QString> robotParams;
    QJsonArray robots = loadDoc["robots"].toArray();
    for (int robotIndex = 0; robotIndex < robots.size(); ++robotIndex) {
            QJsonObject robotObject = robots[robotIndex].toObject();
            int row = robotObject["row"].toInt();
            int col = robotObject["col"].toInt();
            int orientation = robotObject["orientation"].toInt();
            robotParams.append(QString::number(row));
            robotParams.append(QString::number(col));
            robotParams.append(QString::number(orientation));
            //_robots.append(new RobotFieldModel(row,col,0));
    }


    writeToServer("ROBOT", robotParams);


    // Read dockers and write to server
    QVector<QString> dockerParams;
    QJsonArray dockers = loadDoc["dockers"].toArray();
    for (int dockerIndex = 0; dockerIndex < dockers.size(); ++dockerIndex) {
            QJsonObject dockerObject = dockers[dockerIndex].toObject();
            int row = dockerObject["row"].toInt();
            int col = dockerObject["col"].toInt();
            dockerParams.append(QString::number(row));
            dockerParams.append(QString::number(col));
    }


    writeToServer("DOCKER", dockerParams);

    // Read shelves and write to server
    QVector<QString> shelfParams;
    QJsonArray shelves = loadDoc["shelves"].toArray();
    for (int shelfIndex = 0; shelfIndex < shelves.size(); ++shelfIndex) {
            QJsonObject shelfObject = shelves[shelfIndex].toObject();
            int row = shelfObject["row"].toInt();
            int col = shelfObject["col"].toInt();
            shelfParams.append(QString::number(row));
            shelfParams.append(QString::number(col));
            _shelves.append(new ShelfFieldModel(row,col));
    }


    writeToServer("SHELF", shelfParams);

    // Read products and write to server
    _products.clear();
    QVector<QString> productParams;
    QJsonArray products = loadDoc["products"].toArray();
    for (int productIndex = 0; productIndex < products.size(); ++productIndex) {
            QJsonObject productObject = products[productIndex].toObject();
            QString name = productObject["name"].toString();
            int shelf = productObject["shelf"].toInt();
            productParams.append(name);
            productParams.append(QString::number(shelf));
            _products.append(new ProductModel(name, shelf));
    }


    writeToServer("PRODUCT", productParams);

    // Read dropoffs and write to server
    QVector<QString> dropOffParams;
    QJsonArray dropOffs = loadDoc["dropoffs"].toArray();
    for (int dropOffIndex = 0; dropOffIndex < dropOffs.size(); ++dropOffIndex) {
            QJsonObject dropOffObject = dropOffs[dropOffIndex].toObject();
            int row = dropOffObject["row"].toInt();
            int col = dropOffObject["col"].toInt();
            QString product = dropOffObject["product"].toString();
            dropOffParams.append(QString::number(row));
            dropOffParams.append(QString::number(col));
            dropOffParams.append(product);
    }


    writeToServer("DROPOFF", dropOffParams);

    // Read orders and write to server
    QVector<QString> orderParams;
    QJsonArray orders = loadDoc["orders"].toArray();
    for (int orderIndex = 0; orderIndex < orders.size(); ++orderIndex) {
            QString order = orders[orderIndex].toString();
            orderParams.append(order);
            _orders.append(order);
    }


    writeToServer("ORDER", orderParams);


    QObject::connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readFromServer()));
    QObject::connect(_socket, SIGNAL(connected()), this, SLOT(onConnect()));
}

void Connection::readFromServer() {

    QString str = QString::fromUtf8(_socket->readAll());

    qInfo() << str;


    QVector<QString> allmsg = str.split("END");

    foreach (QString msg, allmsg) {
        if (msg != "") {
            msg = msg.trimmed();
            QVector<QString> args = msg.split(" ");
            qDebug() << "[Server] Message from server: " << args.join(" ");
            QString header = args[0];
            args.remove(0);
            processMessage(header, args);
        }

    }


}

void Connection::writeToServer(QString header, QVector<QString> params) {
    QString msg = header + " ";
    for (int i=0; i<params.length(); i++) {
        msg += params[i] + " ";
    }

    msg += "END";


    _socket->write(msg.toUtf8());
}


void Connection::handleError(QAbstractSocket::SocketError) {
}

void Connection::processMessage(QString header, QVector<QString> params) {
    if (header == "SIZE") {
        // params[0]: size
        if (params.length() == 1) {
            int size = params[0].toInt();
            emit createMap(size);
            _size = size;

        }
    } else if (header == "CONNECT") {
        if (params.length() == 1) {
            if (params[0] == "SUCCESS") {
                _error = false;
                emit connected();
            }
        }
    } else if (header == "FAIL") {
        _error = true;
    } else if (header == "ROBOT") {
        if (params.length() > 0 && params.length() % 4 == 0) {
            _robots.clear();
            for (int i = 0; i < params.length(); i+=4) {
                /*
                 * params[i]: row
                 * params[i+1]: col
                 * params[i+2]: orientation
                 * params[i+3]: battery
                 */
                emit fieldToRobot(params[i].toInt(), params[i+1].toInt(), params[i+2].toInt(), params[i+3].toInt());
                _robots.append(new RobotFieldModel(params[i].toInt(), params[i+1].toInt(), params[i+2].toInt(), params[i+3].toInt()));
            }

        }
    } else if (header == "DOCKER" ) {
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+= 2) {
                /*
                 * params[i]: row
                 * params[i+1]: col
                 */
                emit fieldToDocker(params[i].toInt(), params[i+1].toInt());
            }

        }
    } else if (header == "SHELF") {
        _shelves.clear();
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+=2) {
                /*
                 * params[i]: row
                 * params[i+1]: col
                 */
                _shelves.append(new ShelfFieldModel(params[i].toInt(),params[i+1].toInt()));
                emit fieldToShelf(params[i].toInt(), params[i+1].toInt());
            }

        }
    } else if (header == "PRODUCTS") {
        _products.clear();
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+=2) {
                /*
                 * params[i]: name
                 * params[i+1]: shelf
                 */
                //->addProduct(params[i], params[i].toInt());
                _products.append(new ProductModel(params[i],params[i+1].toInt()));
            }

        }
    } else if (header == "ORDERED") {
        if (params.length() > 0) {
            _orders.clear();
            for (int i = 0; i < params.length(); i++) {
                _orders.append(params[i]);
            }

        }
    } else if (header == "DROPOFF") {
        _dropOffPoints.clear();
        if (params.length() > 0 && params.length() % 3 == 0) {
            for (int i = 0; i < params.length(); i+=3) {
                _dropOffPoints.append(new DropOffPointFieldModel(params[i].toInt(),params[i+1].toInt(),params[i+2]));
                /*
                 * params[i]: row
                 * params[i+1]: col
                 * params[i+2]: product
                 */
                emit fieldToDropOff(params[i].toInt(), params[i+1].toInt(),params[i+2]);
            }

        }
    } else if (header == "PAUSED") {
        emit pauseStateChanged(params[0] == "1" ? true : false);
    }
    else if (header == "RESUMED") {
            emit pauseStateChanged(params[0] == "1" ? true : false);
    }

}

void Connection::pauseState()
{
    QVector<QString> args;
    writeToServer("PAUSE", args);
}

void Connection::resumeState()
{
    QVector<QString> args;
    writeToServer("RESUME", args);
}

void Connection::onConnect() {

}

bool Connection::isSuccessful() {
    return !_error;
}

QPair<Connection::FieldTypes, QObject*> Connection::getField(int row, int col)
{
    for(int i=0; i<_shelves.count();i++) {
        if(_shelves[i]->getRow() == row && _shelves[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(Shelf, _shelves[i]);
        }
    }

    for(int i=0; i<_robots.count();i++) {
        if(_robots[i]->getRow() == row && _robots[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(Robot, _robots[i]);
        }
    }

    return QPair<FieldTypes,QObject*> (Empty,nullptr);
}

QVector<QString> Connection::getProductsOnShelf(int row, int col)
{
    int i = 0;
    while (i < _shelves.size() && !(_shelves[i]->getRow() == row && _shelves[i]->getCol() == col)) {
        i++;
    }
    QVector<QString> l;

    for(int j=0; j<_products.size();j++) {
        if(_products[j]->getShelf() == i) {
            l.append(_products[j]->getName());
        }
    }
    return l;
}

void Connection::disconnectSimulation()
{
    QVector<QString> args;
    _products.clear();
    _robots.clear();
    _shelves.clear();
    _dropOffPoints.clear();
    _orders.clear();
    writeToServer("CLOSE", args);
}

void Connection::newOrder()
{
    QVector<QString> args;

    for(int i = 0; i< _newOrders.length(); i++) {
        args.append(_newOrders[i]);
    }
    writeToServer("NEWORDER", args);

}

void Connection::finishSimulation()
{
    QVector<QString> args;
    _products.clear();
    _robots.clear();
    _shelves.clear();
    _dropOffPoints.clear();
    _orders.clear();
    writeToServer("STOP", args);
}

void Connection::addNewOrders(QVector<QString> newOrders)
{
    _newOrders.clear();
    for(int i = 0; i< newOrders.length(); i++){
        _newOrders.append(newOrders[i]);
       // _orders.append(newOrders[i]);
    }
}

QVector<ProductModel *> Connection::getProducts()
{
    return _products;
}



bool Connection::robotOnField(int row, int col)
{
    for(RobotFieldModel* r : _robots) {
        if(r->getRow() == row && r->getCol() == col) return true;
    }
    return false;
}

bool Connection::dropOffInPosition(int row, int col)
{
    for(DropOffPointFieldModel* d : _dropOffPoints)
    {
        if(d->getRow() == row && d->getCol() == col) return true;
    }
    return false;
}

int Connection::getSize() const
{
    return _size;
}

QVector<QString> Connection::getNewOrders()
{
    return _newOrders;
}

QVector<QString> Connection::getOrders()
{
    QVector<QString> l;

    for(int j=0; j<_orders.size();j++) {
            l.append(_orders[j]);
    }
    return l;
}
