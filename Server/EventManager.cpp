#include "EventManager.h"

EventManager::EventManager(Controller* controller, QObject *parent) : QObject(parent), _controller(controller)
{
    _running = false;
}

void EventManager::addConnection(QTcpSocket *connection) {
    _connections.append(connection);
    connect(connection, &QAbstractSocket::disconnected, connection, &QObject::deleteLater);
    connect(connection, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    sendMessageToAll("CONNECT", QVector<QString>("SUCCESS"));
    //sendCurrentState
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

    } else {
        if (header == "STOP") {
            _controller->stopSimulation();
            _running = false;
        } else if (header == "PAUSE") {
            _controller->pauseSimulation();
        } else if (header == "RESUME") {
            _controller->resumeSimulation();
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
