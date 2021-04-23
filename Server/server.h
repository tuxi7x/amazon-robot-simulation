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


/**
 * This is the class which is instantiated by the entry point of the
 * program (the main class)
 * This class implements a TCP server, and holds the EventManager and Controller objects
 * On creation, the class starts to listen on the default public IP address and on port 1432.
 * @brief Server class implementing a TCP server
 *
 */
class Server : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Server constructor
     * @param parent Optional parent object
     */
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
