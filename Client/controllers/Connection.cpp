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

void Connection::connectAndSend(QString host, int port, QFile file) {
    _socket->connectToHost(host, port);


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
    writeToServer("HELLOALL", QVector<QString>("hello all!"));
}
