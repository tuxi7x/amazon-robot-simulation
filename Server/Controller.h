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
#include <QSet>
#include "QFile"
#include "QDate"
#include <models/PathNode.h>



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
    void alreadyOrdered(QString name);
    void setSize(int size);
    void setSpeed(int speed);

    QVector<Robot*> getRobots();
    QVector<Docker*> getDockers();
    QVector<DropOffPoint*> getDropOffPoints();
    QVector<Shelf*> getShelves();
    QVector<Product*> getProducts();
    QVector<QString> getOrders();
    QVector<QString> getAlreadyOrdered();
    int getSize();
    int getSpeed();
    bool getPaused();

    void startSimulation();
    void stopSimulation();
    void pauseSimulation();
    void resumeSimulation();
    int sumConsumedEnergy();

private:
    QVector<Robot*> _robots;
    QVector<Docker*> _dockers;
    QVector<DropOffPoint*> _dropOffPoints;
    QVector<Shelf*> _shelves;
    QVector<Product*> _products;
    QVector<QString> _orders;
    QVector<QString> _alreadyOrdered;
    //The timetable is used by the pathfinding algorithm to determine whether a certain node is free at a given time
    QSet<PathNode> _timeTable;
    int _size;
    QTimer* _timer;
    int _elapsedTime;
    bool _paused;
    int _speed;
    int _steps;
    bool saveGame();

    //Tries to find a path with a robot to a certain destination. Adds the route to the route stack of the robot. Returns true if there was a path
    bool planPathForRobot (Robot* r, int destinationRow, int destinationCol);
    int calculateHeuristicValue(int startX, int startY, int goalX, int goalY);
    int calculateGValue (int startX, int startY, int goalX, int goalY, int startTime, int goalTime);
    bool fieldIsValid (int row, int col, Robot* r, int goalRow, int goalCol);
    int nextOrientation (int orientation);
    int prevOrientation (int orientation);
    Shelf* getShelfWithPosition (int row, int col);
    DropOffPoint* getDropOffPointForProduct (QString product);
    Docker* getNearestDocker (Robot* r);
    void removeProduct (Product* p);
    Product* getProductWithName (QString product);
    Robot* getRobotNearestToShelf (Shelf* s);
    Docker* getDockerWithPosition (int row, int col);
    bool freeInTable(PathNode p, Robot* r);

private slots:
    void tickHandler();

signals:
    void updateState();


};

#endif // CONTROLLER_H
