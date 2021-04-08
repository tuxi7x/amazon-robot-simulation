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

class EventManager : public QObject
{
    Q_OBJECT
public:
    explicit EventManager(Controller* controller, QObject *parent = nullptr);

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
