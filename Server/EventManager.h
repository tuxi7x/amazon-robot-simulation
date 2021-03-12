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

class EventManager : public QObject
{
    Q_OBJECT
public:
    explicit EventManager(QObject *parent = nullptr);

    void addConnection(QTcpSocket* connection);


signals:

private:
    QVector<QTcpSocket*> _connections;
    void processMesage(QString header, QVector<QString> params, QTcpSocket* connection);
    void sendMessageToAll(QString header, QVector<QString> params);


public slots:
    void ReadyRead();

};

#endif // EVENTMANAGER_H
