#include "EventManager.h"

EventManager::EventManager(Controller* controller, QObject *parent) : QObject(parent), _controller(controller)
{
    _running = false;
}

void EventManager::addConnection(QTcpSocket *connection) {
    _connections.append(connection);
    connect(connection, &QAbstractSocket::disconnected, connection, &QObject::deleteLater);
    connect(connection, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    sendMessageToOne(connection, "CONNECT", QVector<QString>("SUCCESS"));

}

void EventManager::ReadyRead(){

    QObject* senderObj = sender();
    QTcpSocket* connection = qobject_cast<QTcpSocket*>(senderObj);
    QString str = QString::fromUtf8(connection->readAll());

    QVector<QString> allmsg = str.split("END");

    foreach (QString msg, allmsg) {
        if (msg != "") {
            msg = msg.trimmed();
            QVector<QString> args = msg.split(" ");
            qDebug() << "[Server] Message from client: " << args.join(" ");
            QString header = args[0];
            args.remove(0);
            processMessage(header, args, connection);
        }

    }
}

void EventManager::processMessage(QString header, QVector<QString> params, QTcpSocket* sender) {


    if (header == "CLOSE") {
        sender->disconnectFromHost();
        sender = nullptr;
    } else if (header == "ORDER") {
        if (params.length() > 0) {
           for (int i=0; i<params.length(); i++) {
               // params[i]: order
               _controller->addOrder(params[i]);
           }
        }
    } else if (header == "PAUSE") {
    _controller->pauseSimulation();
    sendMessageToAll("PAUSED", QVector<QString>(QString::number(_controller->getPaused())));
 } else if (header == "RESUME") {
    _controller->resumeSimulation();
    sendMessageToAll("RESUMED", QVector<QString>(QString::number(_controller->getPaused())));

}
    if (!_running) {

        if (header == "SIZE") {
            // params[0]: size
            if (params.length() == 1) {
                int size = params[0].toInt();
                _controller->setSize(size);

            }


        } else if (header == "ROBOT") {
            if (params.length() > 0 && params.length() % 3 == 0) {
                for (int i = 0; i < params.length(); i+=3) {
                    /*
                     * params[i]: row
                     * params[i+1]: col
                     * params[i+2]: orientation
                     */
                    _controller->addRobot(params[i].toInt(), params[i+1].toInt(), params[i+2].toInt());
                }

            }
        } else if (header == "DOCKER" ) {
            if (params.length() > 0 && params.length() % 2 == 0) {
                for (int i = 0; i < params.length(); i+= 2) {
                    /*
                     * params[i]: row
                     * params[i+1]: col
                     */
                    _controller->addDocker(params[i].toInt(), params[i+1].toInt());
                }

            }
        } else if (header == "SHELF") {
            if (params.length() > 0 && params.length() % 2 == 0) {
                for (int i = 0; i < params.length(); i+=2) {
                    /*
                     * params[i]: row
                     * params[i+1]: col
                     */
                    _controller->addShelf(params[i].toInt(), params[i+1].toInt());
                }

            }
        } else if (header == "PRODUCT") {
            if (params.length() > 0 && params.length() % 2 == 0) {
                for (int i = 0; i < params.length(); i+=2) {
                    /*
                     * params[i]: name
                     * params[i+1]: shelf
                     */
                    _controller->addProduct(params[i], params[i].toInt());
                }

            }
        } else if (header == "DROPOFF") {
            if (params.length() > 0 && params.length() % 3 == 0) {
                for (int i = 0; i < params.length(); i+=3) {
                    /*
                     * params[i]: row
                     * params[i+1]: col
                     * params[i+2]: product
                     */
                    _controller->addDropOffPoint(params[i].toInt(), params[i+1].toInt(), params[i+2]);
                }

            }
        }

        if (_controller->getRobots().size() > 0 && _controller->getDockers().size() > 0 && _controller->getDropOffPoints().size() > 0 && _controller->getProducts().size() > 0 && _controller->getShelves().size() > 0 && _controller->getSize() > -1) {
            _running = true;
            _controller->startSimulation();
            sendCurrentStateToAll();
        }
    } else {
        if (header == "STOP") {
            _controller->stopSimulation();
            _running = false;
        } else if (header == "PAUSE") {
            _controller->pauseSimulation();
            sendMessageToAll("PAUSED", QVector<QString>(QString::number(_controller->getPaused())));
         } else if (header == "RESUME") {
            _controller->resumeSimulation();
            sendMessageToAll("RESUMED", QVector<QString>(QString::number(_controller->getPaused())));
        } else if (header == "SPEED") {
            if (params.length() == 1) {
                int speed = params[0].toInt();
                _controller->setSpeed(speed);
            }
        }
    }


}

void EventManager::sendMessageToAll(QString header, QVector<QString> params) {
    QString msg = header + " ";
    for (int i=0; i<params.length(); i++) {
        msg += params[i] + " ";

    }

    msg += "END";

    foreach (QTcpSocket* connection, _connections) {
        connection->write(msg.toUtf8());
    }
}

void EventManager::sendMessageToOne(QTcpSocket* client, QString header, QVector<QString> params) {
    QString msg = header + " ";
    for (int i=0; i<params.length(); i++) {
        msg += params[i] + " ";

    }

    msg += "END";

    client->write(msg.toUtf8());
}

void EventManager::sendCurrentStateToOne(QTcpSocket* client) {
    int size = _controller->getSize();
    int speed = _controller->getSpeed();
    QVector<Robot*> robots = _controller->getRobots();
    QVector<Docker*> dockers = _controller->getDockers();
    QVector<DropOffPoint*> dropoffs = _controller->getDropOffPoints();
    QVector<Shelf*> shelves = _controller->getShelves();
    QVector<QString> orders = _controller->getOrders();
    QVector<Product*> products = _controller->getProducts();

    // Send size
    sendMessageToOne(client, "SIZE", QVector<QString>(QString::number(size)));
    // Send speed
    sendMessageToOne(client, "SPEED", QVector<QString>(QString::number(speed)));

    // Send robots
    QVector<QString> robotParams;
    for (int i=0; i<robots.size(); i++) {
        robotParams.append(QString::number(robots[i]->getRow()));
        robotParams.append(QString::number(robots[i]->getCol()));
        robotParams.append(QString::number(robots[i]->getDirection()));
        robotParams.append(QString::number(robots[i]->getBattery()));
    }
    sendMessageToOne(client, "ROBOT", robotParams);

    // Send dockers
    QVector<QString> dockerParams;
    for (int i=0; i<dockers.size(); i++) {
        dockerParams.append(QString::number(dockers[i]->getRow()));
        dockerParams.append(QString::number(dockers[i]->getCol()));
    }
    sendMessageToOne(client, "DOCKER", dockerParams);

    // Send dropoffs
    QVector<QString> dropoffParams;
    for (int i=0; i<dropoffs.size(); i++) {
        dropoffParams.append(QString::number(dropoffs[i]->getRow()));
        dropoffParams.append(QString::number(dropoffs[i]->getCol()));
        dropoffParams.append(dropoffs[i]->getProduct());
    }
    sendMessageToOne(client, "DROPOFF", dropoffParams);

    // Send shelves
    QVector<QString> shelfParams;
    for (int i=0; i<shelves.size(); i++) {
        shelfParams.append(QString::number(shelves[i]->getRow()));
        shelfParams.append(QString::number(shelves[i]->getCol()));
    }
    sendMessageToOne(client, "SHELF", shelfParams);

    // Send orders
    sendMessageToOne(client, "ORDER", orders);

    // Send products
    QVector<QString> productParams;
    for (int i=0; i<products.size(); i++) {
        productParams.append(products[i]->getName());
        productParams.append(QString::number(products[i]->getShelf()));
    }
    sendMessageToOne(client, "PRODUCTS", productParams);
}

void EventManager::sendCurrentStateToAll() {
    int size = _controller->getSize();
    int speed = _controller->getSpeed();
    QVector<Robot*> robots = _controller->getRobots();
    QVector<Docker*> dockers = _controller->getDockers();
    QVector<DropOffPoint*> dropoffs = _controller->getDropOffPoints();
    QVector<Shelf*> shelves = _controller->getShelves();
    QVector<QString> orders = _controller->getOrders();
    QVector<Product*> products = _controller->getProducts();

    // Send size
    sendMessageToAll("SIZE", QVector<QString>(QString::number(size)));
    // Send speed
    sendMessageToAll("SPEED", QVector<QString>(QString::number(speed)));

    // Send robots
    QVector<QString> robotParams;
    for (int i=0; i<robots.size(); i++) {
        robotParams.append(QString::number(robots[i]->getRow()));
        robotParams.append(QString::number(robots[i]->getCol()));
        robotParams.append(QString::number(robots[i]->getDirection()));
        robotParams.append(QString::number(robots[i]->getBattery()));
    }
    sendMessageToAll("ROBOT", robotParams);

    // Send dockers
    QVector<QString> dockerParams;
    for (int i=0; i<dockers.size(); i++) {
        dockerParams.append(QString::number(dockers[i]->getRow()));
        dockerParams.append(QString::number(dockers[i]->getCol()));
    }
    sendMessageToAll("DOCKER", dockerParams);

    // Send dropoffs
    QVector<QString> dropoffParams;
    for (int i=0; i<dropoffs.size(); i++) {
        dropoffParams.append(QString::number(dropoffs[i]->getRow()));
        dropoffParams.append(QString::number(dropoffs[i]->getCol()));
        dropoffParams.append(dropoffs[i]->getProduct());
    }
    sendMessageToAll("DROPOFF", dropoffParams);

    // Send shelves
    QVector<QString> shelfParams;
    for (int i=0; i<shelves.size(); i++) {
        shelfParams.append(QString::number(shelves[i]->getRow()));
        shelfParams.append(QString::number(shelves[i]->getCol()));
    }
    sendMessageToAll("SHELF", shelfParams);

    // Send orders
    sendMessageToAll("ORDER", orders);

    // Send products
    QVector<QString> productParams;
    for (int i=0; i<products.size(); i++) {
        productParams.append(products[i]->getName());
        productParams.append(QString::number(products[i]->getShelf()));
    }
    sendMessageToAll("PRODUCTS", productParams);
}
