#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QStack>
#include "models/Shelf.h"
#include "models/Product.h"
#include "PathNode.h"

/**
 * @brief Enum for storing the current state of a robot
 */
enum RobotStates {FREE, GOINGFORSHELF, TAKINGSHELF, TAKINGSHELFBACK, GOINGTOCHARGER, CHARGING};

/**
 * Robot Model class which ships with methods used for moving the robot
 * @brief Model class containing information about a robot
 */
class Robot : public QObject
{
    Q_OBJECT
public:
   explicit Robot(QObject* parent = nullptr);
   Robot(int row, int col, int direction);

   int getRow();
   int getCol();
   int getDirection();
   int getBattery();
   void pushToPath(PathNode* x);
   bool pathIsEmpty();
   PathNode* stepOnPath();
   int getOriginalRow() const;
   int getOriginalCol() const;

    RobotStates getState() const;
    void setState(const RobotStates &state);

    void setCurrentShelf(Shelf *currentShelf);

    int getMaxBattery() const;

    Product *getCurrentProduct() const;
    void setCurrentProduct(Product *currentProduct);
    void clearPath();
    Shelf *getCurrentShelf() const;

    void setBattery(int battery);
    int getConsumedEnergy();

private:
    int _id;
    int _row;
    int _originalRow;
    int _col;
    int _originalCol;
    int _direction;
    int _battery;
    int _maxBattery;
    int _consumedEnergy;
    Shelf* _currentShelf;
    Product* _currentProduct;
    QStack<PathNode*> _robotPath;
    RobotStates _state;
    static int _idCounter;


signals:

};

#endif // ROBOT_H
