#include "EventManager.h"

EventManager::EventManager(QObject *parent) : QObject(parent)
{

}

void EventManager::addConnection(QTcpSocket *connection) {
    _connections.append(connection);
    connect(connection, &QAbstractSocket::disconnected, connection, &QObject::deleteLater);
    connect(connection, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

void EventManager::ReadyRead(){

    QObject* senderObj = sender();
    QTcpSocket* connection = qobject_cast<QTcpSocket*>(senderObj);
    QString str = QString::fromUtf8(connection->readAll());

    qDebug() << "[Server] Message from client: " << str;


    QVector<QString> args = str.split(" ");
    QString header = args[0];
    args.remove(0);
    processMesage(header, args, connection);

}

void EventManager::processMesage(QString header, QVector<QString> params, QTcpSocket* sender) {
    if (header == "CLOSE") {
        sender->disconnectFromHost();
        sender = nullptr;
    } else if (header == "SIZE") {
        int size = params[0].toInt();
        qDebug() << "A pálya mérete: " << size;
    } else if (header == "ROBOT") {
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+=2) {
                // rows and cols of robot placement
                qDebug() << "row: " << params[i] << " col: " << params[i+1];
            }
        }
    } else if (header == "DOCKER" ) {
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+= 2) {
                // rows and cols of docker placement
                qDebug() << "row: " << params[i] << " col: " << params[i+1];
            }
        }
    } else if (header == "ORDER") {
        if (params.length() > 0) {
                // vector for orders
               QVector<QString> orders = QVector<QString>();
               for (int i=0; i<params.length(); i++) {
                   orders.append(params[i]);
               }
        }
    } else if (header == "SHELF") {
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+=2) {
                // rows and cols of shelves placement
                qDebug() << "row: " << params[i] << " col: " << params[i+1];
            }
        }
    } else if (header == "PRODUCT") {
        if (params.length() > 0 && params.length() % 2 == 0) {
            for (int i = 0; i < params.length(); i+=2) {
                // name and shelf of product
                qDebug() << "name: " << params[i] << " shelf: " << params[i+1];
            }
        }
    } else if (header == "DROPOFF") {
        if (params.length() > 0 && params.length() % 3 == 0) {
            for (int i = 0; i < params.length(); i+=3) {
                // rows and cols of shelves placement
                qDebug() << "row: " << params[i] << " col: " << params[i+1] << " product:" << params[i+2];
            }
        }
    }
}

void EventManager::sendMessageToAll(QString header, QVector<QString> params) {
    QString msg = header + " ";
    for (int i=0; i<params.length(); i++) {
        msg += params[i];
        if (i != params.length() -1) {
            msg += " ";
        }
    }

    foreach (QTcpSocket* connection, _connections) {
        connection->write(msg.toUtf8());
    }
}
