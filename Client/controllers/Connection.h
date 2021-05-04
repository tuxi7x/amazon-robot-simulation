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

/**
 * @brief The Connection class handles the connection to the server side application.
 * It sends all the necesary information when the user wants to start a new simulation.
 * It handles the information sent by the server about this simulation.
 */
class Connection : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Connection Default constructor.
     * @param parent parent of this QObject
     */
    explicit Connection(QObject *parent = nullptr);
    /**
     * @brief The FieldTypes enum represents the type of fields that are used during the simulation.
     */
    enum FieldTypes {Empty, Robot, Shelf, Docker, DropOffPoint};
    /**
     * @brief connect tries to connect to a simulation server with the given ip address and port.
     * @param host The ip of the server.
     * @param port The port of the server.
     */
    void connect(QString host, int port);
    /**
     * @brief connectAndSend tries to connect to a simulation server with the given ip address and port but also sends the information about this simulation to the server.
     * @param host The ip of the server.
     * @param port The port of the server.
     * @param file The file containg the information about the simulation.
     */
    void connectAndSend(QString host, int port, QFile* file);
    /**
     * @brief writeToServer with this method it is possible to write different information to the server application. You can send a header and arguments of that header.
     * @param header The header of the message.
     * @param params The parameters of the message.
     */
    void writeToServer(QString header, QVector<QString> params);
    /**
     * @brief processMessage processes a message sent by the server.
     * @param header the header of the message processed.
     * @param params the parameters of the message processed.
     */
    void processMessage(QString header, QVector<QString> params);
    /**
     * @brief isSuccessful Used to check whether the sonnecting was successful
     * @return a bool containg the information whether connectiong was successful.
     */
    bool isSuccessful();
    /**
     * @brief pauseState sends a message to the server to pause the simulation.
     */
    void pauseState();
    /**
     * @brief resumeState sends a message to the server to resume the simulation.
     */
    void resumeState();
    /**
     * @brief finishSimulation sends a message to the server to finish the simulation.
     */
    void finishSimulation();
    /**
     * @brief disconnectSimulation sends a message to the server that the client wants to disconnect from the simulation.
     */
    void disconnectSimulation();
    /**
     * @brief newOrder sends a new order to the simulation.
     */
    void newOrder();
    /**
     * @brief getField Check the type of the field in a given position.
     * @param row the row of the field.
     * @param col the column of the field.
     * @return
     */
    QPair<FieldTypes, QObject*> getField (int row, int col);
    /**
     * @brief getProductsOnShelf gets the name of the products on a shelf with a given position
     * @param row the row of the shelf.
     * @param col the column of the shelf
     * @return  the products in a vector as QString
     */
    QVector<QString> getProductsOnShelf(int row, int col);
    /**
     * @brief getOrders Gets the orders that were placed during the simulation.
     * @return The orders as QStrings
     */
    QVector<QString> getOrders();
    /**
     * @brief addNewOrders Adds the new orders (?)
     * @param newOrders The new orders.
     */
    void addNewOrders(QVector<QString> newOrders);
    /**
     * @brief getProducts returns the name of all of the products in the warehouse.
     * @return the name of the products in a vector as QStrings
     */
    QVector<ProductModel *> getProducts();
    /**
     * @brief getOriginalProducts Gets the products that were originally in the warehouse at the start of the simulation.
     * @return the name of the products.
     */
    QVector<ProductModel *> getOriginalProducts();
    /**
     * @brief getSize returns the size of simulation
     * @return the size of the warehouse as an int.
     */
    int getSize() const;
    /**
     * @brief dropOffInPosition Checks whether there is a drop off point in the given poistion.
     * @param row the row we want to check
     * @param col the column we want to check.
     * @return whether there is a dropoff in the given position
     */
    bool dropOffInPosition(int row, int col);
    /**
     * @brief robotOnField Checks whether there is a Robot in the given poistion.
     * @param row the row we want to check
     * @param col the column we want to check.
     * @return whether there is a Robot in the given position
     */
    bool robotOnField(int row, int col);
    /**
     * @brief speedChanged A function called by the simulation window when the simulation speedd was changed and we need to send it to the server.
     * @param newSpeed The new speed (value from 1 to 3)
     */
    void speedChanged(int newSpeed);

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
    QVector <QString> _newOrders;

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
    void fieldToDropOff (int row, int col, QString product);
    void fieldToDocker (int row, int col);
    void gameSpeedChanged (int newSpeed);
    void pauseStateChanged (bool paused);
    void connected();
    void productDelivered (QString prodName);
};

#endif // CONNECTION_H
