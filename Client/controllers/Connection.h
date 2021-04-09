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
#include <QDebug>
#include <QAbstractSocket>
#include "models/DockerFieldModel.h"
#include "models/DropOffPointFieldModel.h"
#include "models/ProductModel.h"
#include "models/RobotFieldModel.h"
#include "models/ShelfFieldModel.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};
    void connect(QString host, int port);
    void connectAndSend(QString host, int port, QFile* file);

    void writeToServer(QString header, QVector<QString> params);
    void processMessage(QString header, QVector<QString> params);
    bool isSuccessful();

    void pauseState();
    void resumeState();
    QPair<FieldTypes, QObject*> getField (int row, int col);
    QVector<QString> getProductsOnShelf(int row, int col);

private:
    QTcpSocket* _socket;
    bool _error;
    int _size;
    QVector<RobotFieldModel*> _robots;
    QVector <ShelfFieldModel*> _shelves;
    QVector <DockerFieldModel*> _dockers;
    QVector <DropOffPointFieldModel*> _dropOffPoints;
    QVector <ProductModel*> _products;
    QVector <QString> _orders;

private slots:
    void readFromServer();
    void onConnect();

    void handleError(QAbstractSocket::SocketError);



signals:
    void createMap (int size);
    //Orientations: 0 = up, 1 = right, 2 = down, 3 = left
    void fieldToRobot (int row, int col, int orientation, int battery);
    void fieldToEmpty (int row, int col);
    void fieldToShelf (int row, int col);
    void fieldToDropOff (int row, int col);
    void fieldToDocker (int row, int col);
    void gameSpeedChanged (int newSpeed);
    void pauseStateChanged (bool paused);
    void connected();
};

#endif // CONNECTION_H
