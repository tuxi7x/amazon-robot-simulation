#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QDebug>
#include <QString>
#include "EventManager.h"
#include "Controller.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:
    void initServer();

    QTcpServer* _tcpServer;
    EventManager* _eventManager;
    Controller* _controller;

private slots:
    void startConnection();



signals:

};

#endif // SERVER_H
