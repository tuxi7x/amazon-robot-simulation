#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QByteArray>


class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    void connect(QString host, int port);
    void connectAndSend(QString host, int port, QFile file);

private:
    QTcpSocket* _socket;

private slots:
    void ReadyRead();
    void handleError();



signals:

};

#endif // CONNECTION_H
