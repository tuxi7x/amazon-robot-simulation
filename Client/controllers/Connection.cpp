#include "Connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket();

}


void Connection::connect(QString host, int port) {
    _socket->connectToHost(host, port);

    //QObject::connect(_socket, SIGNAL(errorOccurred()), this, SLOT(handleError()));
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

void Connection::connectAndSend(QString host, int port, QFile file) {
    _socket->connectToHost(host, port);


}

void Connection::ReadyRead() {

    QString msg = "Hello szerver! :)";

    _socket->write(msg.toUtf8());

}


void Connection::handleError() {

}
