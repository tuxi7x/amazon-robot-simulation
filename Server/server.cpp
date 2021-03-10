#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    _tcpServer = new QTcpServer(this);
    if (!_tcpServer->listen(QHostAddress::Any, 1243)) {
            exit(1);
            return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    qInfo() << (tr("The server is running on IP: %1 Port: %2").arg(ipAddress).arg(_tcpServer->serverPort()));

    _eventManager = new EventManager();


    connect(_tcpServer, &QTcpServer::newConnection, this, &Server::startConnection);

}
void Server::startConnection() {
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_10);

    out << "Hello client";
    QTcpSocket* _connection = _tcpServer->nextPendingConnection();
    _connection->write(block);
    _eventManager->addConnection(_connection);





}


