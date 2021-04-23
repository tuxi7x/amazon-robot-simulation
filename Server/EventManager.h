#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QIODevice>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QVector>
#include "Controller.h"

/**
 * This class holds all the connected clients and listens for incoming messages,
 * and when processesed, it interacts with the Controller object.
 * Also this class is responsible for sending the messages to every client.
 * @brief EventManager Class for managing event-based communication with the clients
 */
class EventManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief EventManager Constructor for EventManager class
     * @param controller Controller object supplied by the Server class (Dependency Injection Pattern)
     * @param parent Optional parent parameter
     */
    explicit EventManager(Controller* controller, QObject *parent = nullptr);

    /**
     * The Server class adds connected clients to the simulation using this method.
     * @brief addConnection Adds the given object to the connections, and begins to listen to incoming messages, and send outgoing messages
     * @param connection QTCPSocket pointer object containing information about the client
     */
    void addConnection(QTcpSocket* connection);


signals:

private:
    QVector<QTcpSocket*> _connections;
    void processMessage(QString header, QVector<QString> params, QTcpSocket* connection);
    void sendMessageToAll(QString header, QVector<QString> params);
    void sendCurrentStateToAll();
    void sendCurrentStateToOne(QTcpSocket* client);
    void sendMessageToOne(QTcpSocket* client, QString header, QVector<QString> params);


    Controller* _controller;

    bool _running;

public slots:
    void ReadyRead();
    void destroyDisconnectedConnection();

};

#endif // EVENTMANAGER_H
