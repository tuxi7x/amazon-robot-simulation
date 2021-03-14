#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    void connect(QString host, int port);
    void connectAndSend(QString host, int port, QFile* file);

    void writeToServer(QString header, QVector<QString> params);
    void processMessage(QString header, QVector<QString> params);

private:
    QTcpSocket* _socket;

private slots:
    void readFromServer();
    void onConnect();

    void handleError();



signals:

};

#endif // CONNECTION_H
