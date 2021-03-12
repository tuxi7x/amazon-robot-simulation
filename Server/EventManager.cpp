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
                qDebug() << "row: " << params[i] << " col: " << params[i+1];
            }
        }
    } else if (header == "HELLOALL") {
        sendMessageToAll("HELLOALL", QVector<QString> {"Hello all!"});
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
