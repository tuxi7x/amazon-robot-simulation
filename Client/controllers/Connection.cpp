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

    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);


    out.setVersion(QDataStream::Qt_5_10);

    out << "Hello Server";


    _socket->write(block);

}


void Connection::handleError() {

}
