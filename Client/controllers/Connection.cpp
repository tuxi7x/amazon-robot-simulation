#include "Connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket();

}


void Connection::connect(QString host, int port) {
    _socket->connectToHost(host, port);

    //QObject::connect(_socket, SIGNAL(errorOccurred()), this, SLOT(handleError()));
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readFromServer()));
    QObject::connect(_socket, SIGNAL(connected()), this, SLOT(onConnect()));
}

void Connection::connectAndSend(QString host, int port, QFile* file) {
    _socket->connectToHost(host, port);

    if (!file->open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return;
    }

    // Read file and convert to Json
    QByteArray saveData = file->readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));


    // Read size and write to server
    QVector<QString> sizeParams;
    sizeParams.append(QString::number(loadDoc["size"].toInt()));
    sizeParams.append("END");
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
    }

    robotParams.append("END");

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

    dockerParams.append("END");

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
    }

    shelfParams.append("END");

    writeToServer("SHELF", shelfParams);

    // Read products and write to server
    QVector<QString> productParams;
    QJsonArray products = loadDoc["products"].toArray();
    for (int productIndex = 0; productIndex < products.size(); ++productIndex) {
            QJsonObject productObject = products[productIndex].toObject();
            QString name = productObject["name"].toString();
            int shelf = productObject["shelf"].toInt();
            productParams.append(name);
            productParams.append(QString::number(shelf));
    }

    productParams.append("END");

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

    dropOffParams.append("END");

    writeToServer("DROPOFF", dropOffParams);

    // Read orders and write to server
    QVector<QString> orderParams;
    QJsonArray orders = loadDoc["orders"].toArray();
    for (int orderIndex = 0; orderIndex < orders.size(); ++orderIndex) {
            QString order = orders[orderIndex].toString();
            orderParams.append(order);
    }

    orderParams.append("END");

    writeToServer("ORDER", orderParams);
}

void Connection::readFromServer() {

    QString str = QString::fromUtf8(_socket->readAll());

    QVector<QString> args = str.split(" ");
    QString header = args[0];
    args.remove(0);
    processMessage(header, args);


}

void Connection::writeToServer(QString header, QVector<QString> params) {
    QString msg = header + " ";
    for (int i=0; i<params.length(); i++) {
        msg += params[i];
        if (i != params.length() -1) {
            msg += " ";
        }
    }

    _socket->write(msg.toUtf8());
}


void Connection::handleError() {

}

void Connection::processMessage(QString header, QVector<QString> params) {
    qDebug() << header << params;
}

void Connection::onConnect() {
    //writeToServer("HELLOALL", QVector<QString>("hello all!"));
}
