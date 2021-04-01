#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include "models/Robot.h"
#include "models/Docker.h"
#include "models/DropOffPoint.h"
#include "models/Product.h"
#include "models/Shelf.h"
#include <QTimer>
#include <QDebug>



class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    void addRobot(int row, int col, int orientation);
    void addDocker(int row, int col);
    void addDropOffPoint(int row, int col, QString product);
    void addShelf(int row, int col);
    void addProduct(QString name, int shelf);
    void addOrder(QString name);
    void setSize(int size);
    void setSpeed(int speed);

    QVector<Robot*> getRobots();
    QVector<Docker*> getDockers();
    QVector<DropOffPoint*> getDropOffPoints();
    QVector<Shelf*> getShelves();
    QVector<Product*> getProducts();
    QVector<QString> getOrders();
    int getSize();
    int getSpeed();

    void startSimulation();
    void stopSimulation();
    void pauseSimulation();
    void resumeSimulation();

private:
    QVector<Robot*> _robots;
    QVector<Docker*> _dockers;
    QVector<DropOffPoint*> _dropOffPoints;
    QVector<Shelf*> _shelves;
    QVector<Product*> _products;
    QVector<QString> _orders;
    int _size;

    int _speed;


signals:

};

#endif // CONTROLLER_H
