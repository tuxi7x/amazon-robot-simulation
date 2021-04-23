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


/**
 * This class is responsible for the simulation. It holds every information needed using the Model objects, and
 * a pathfinding algorithm is implemented in this class used for finding the most optimal path for the robots used
 * in the simulation. Also uses a signal which is connected to a handler in the EventManager class, which sends the updated state
 * to the clients every tick.
 * @brief Controller class responsible for controlling the simmulation
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Controller Default constructor for Controller class
     * @param parent Optional parent parameter
     */
    explicit Controller(QObject *parent = nullptr);

    /**
     * @brief addRobot Adds a new robot to the simulation (uses the Robot model)
     * @param row The robot's row in a nxn grid
     * @param col The robot's column in an nxn grid
     * @param orientation The direction where the robot is looking (0 - north, 1 - east, 2 - south, 3 - west)
     */
    void addRobot(int row, int col, int orientation);

    /**
     * @brief addDocker Adds a new docker to the simulation (uses the Docker model)
     * @param row The docker's row in a nxn grid
     * @param col The docker's column in an nxn grid
     */
    void addDocker(int row, int col);

    /**
     * @brief addDropOffPoint Adds a new dropoff point to the simulation (uses the DropOffPoint model)
     * @param row The dropoff point's row in a nxn grid
     * @param col The dropoff point's column in an nxn grid
     * @param product The name of the product for the dropoff point
     */
    void addDropOffPoint(int row, int col, QString product);

    /**
     * @brief addShelf Adds a new shelf to the simulation (uses the Shelf model)
     * @param row The shelf's row in a nxn grid
     * @param col The shelf's column in a nxn grid
     */
    void addShelf(int row, int col);

    /**
     * @brief addProduct Adds a new product to the simulation (uses the Product model)
     * @param name The name of the product to be added
     * @param shelf The id of the shelf, which holds the product
     */
    void addProduct(QString name, int shelf);

    /**
     * @brief addOrder Adds a new order to the simulation
     * @param name The name of the product to be ordered
     */
    void addOrder(QString name);

    /**
     * @brief alreadyOrdered Takes note that the product is already ordered
     * @param name The product already ordered
     */
    void alreadyOrdered(QString name);

    /**
     * @brief setSize Sets the size of the simulation grid
     * @param size The new size of the simulation grid
     */
    void setSize(int size);

    /**
     * @brief setSpeed Sets the speed of the simulation
     * @param speed The new speed of the simulation
     */
    void setSpeed(int speed);

    /**
     * @brief getRobots Getter for robots
     * @return A QVector containing Robot* objects
     */
    QVector<Robot*> getRobots();

    /**
     * @brief getDockers Getter for dockers
     * @return A QVector containing Docker* objects
     */
    QVector<Docker*> getDockers();

    /**
     * @brief getDropOffPoints Getter for dropoff points
     * @return A QVector containing DropOffPoint* objects
     */
    QVector<DropOffPoint*> getDropOffPoints();

    /**
     * @brief getShelves Getter for shelves
     * @return A QVector containing Shelf* objects
     */
    QVector<Shelf*> getShelves();

    /**
     * @brief getProducts Getter for products
     * @return A QVector containing Product* objects
     */
    QVector<Product*> getProducts();

    /**
     * @brief getOrders Getter for orders
     * @return A QVector containing the name of the ordered products as QString objects
     */
    QVector<QString> getOrders();

    /**
     * @brief getAlreadyOrdered Getter for already ordered products
     * @return A QVector containing the name of the products already ordered as QString objects
     */
    QVector<QString> getAlreadyOrdered();

    /**
     * @brief getSize Getter for size
     * @return The current size of the simulation grid
     */
    int getSize();

    /**
     * @brief getSpeed Getter for speed
     * @return The current speed of the simulation
     */
    int getSpeed();

    /**
     * @brief getPaused Checks whether the simulation is paused or not
     * @return Returns true if the simulation is paused
     */
    bool getPaused();

    /**
     * @brief startSimulation Starts the simulation
     */
    void startSimulation();

    /**
     * @brief stopSimulation Stops the simulation
     */
    void stopSimulation();

    /**
     * @brief pauseSimulation Pauses the simulation
     */
    void pauseSimulation();

    /**
     * @brief resumeSimulation Resumes the paused simulation
     */
    void resumeSimulation();

    /**
     * @brief sumConsumedEnergy Counts the amount of energy used
     * @return The amount of energy used by the robots during the simulation
     */
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

private slots:
    void tickHandler();

signals:
    void updateState();


};

#endif // CONTROLLER_H
