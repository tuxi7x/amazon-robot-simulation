#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QStack>
#include "models/Shelf.h"
#include "models/Product.h"
#include "PathNode.h"

enum RobotStates {FREE, GOINGFORSHELF, TAKINGSHELF, TAKINGSHELFBACK, GOINGTOCHARGER, CHARGING};

/**
 * Robot Model class which ships with methods used for moving the robot
 * @brief Model class containing information about a robot
 */
class Robot : public QObject
{
    Q_OBJECT
public:
   explicit Robot(QObject *parent = nullptr);
   Robot(int row, int col, int direction);
   /**
    * @brief getRow A getter for the row of the Robot in the warehouse.
    * @return The row of the Robot.
    */
   int getRow();
   /**
    * @brief getCol A getter for the column of the Robot in the warehouse.
    * @return The column of the Robot.
    */
   int getCol();
   /**
    * @brief getDirection A getter for the direction of the Robot.
    * 0 = north, 1 = east, 2 = south, 3 = west.
    * @return The direction of the Robot.
    */
   int getDirection();
   /**
    * @brief getBattery A getter for the current battery of the Robot.
    * @return The current battery as an integer.
    */
   int getBattery();
   /**
    * @brief pushToPath Adds a node to the path stack of the robot. The
    * Robot pop off a PathNode from its Stack in every tick of the Simulation and steps according to that Node.
    * @param x THe PathNode needed to be added to the Stack.
    */
   void pushToPath(PathNode* x);
   /**
    * @brief pathIsEmpty This function is used to check whether the Robot's path is empty or not.
    * @return true if the path is empty and false is it is not empty.
    */
   bool pathIsEmpty();
   /**
    * @brief stepOnPath pops off a PathNode from the Robot's stack and steps according to that Node.
    * it also decreases the battery of the Robot by one.
    * @return true if the step was successful and false if it wasn't.
    */
   PathNode* stepOnPath();
   /**
    * @brief getOriginalRow A getter for the original row of the Robot in the warehouse.
    * @return The original row of the Robot.
    */
   int getOriginalRow() const;
   /**
    * @brief getOriginalCol A getter for the original column of the Robot in the warehouse.
    * @return The original column of the Robot.
    */
   int getOriginalCol() const;
   /**
    * @brief getState A getter for the current state of the Robot. For the possible states see the RobotStates enum type.
    * @return A RobotStates enum type.
    */
   RobotStates getState() const;
   /**
    * @brief setState Sets the current state of the robot. For possible states see the RobotStates enum type.
    * @param state The new state of the Robot.
    */
   void setState(const RobotStates &state);
   /**
    * @brief setCurrentShelf Sets the current shelf carried by this Robot.
    * @param currentShelf The shelf that the robot is holding right now.
    */
   void setCurrentShelf(Shelf *currentShelf);
   /**
    * @brief getMaxBattery Return the maximum battery possible for this Robot.
    * @return The value of the maximum battery.
    */
   int getMaxBattery() const;
   /**
    * @brief getCurrentProduct A getter for the product that the Robot wants to deliver right now.
    * @return The product that the Robot wants to deliver now, or NULL if the Robot isn't delivering.
    */
   Product *getCurrentProduct() const;
   /**
    * @brief setCurrentProduct Sets the product that the Robot wants to deliver right now.
    * @param currentProduct The new Product that the Robot has to deliver.
    */
   void setCurrentProduct(Product *currentProduct);
   /**
    * @brief clearPath Clears the path of the robot. (Sets its Stack to empty)
    */
   void clearPath();
   /**
    * @brief getCurrentShelf A getter for the current Shelf carried by the robot.
    * @return The current Shelf carried or NULL if it isn't carrying a Shelf right now.
    */
   Shelf *getCurrentShelf() const;
   /**
    * @brief setBattery Sets the current battery of the Robot.
    * @param battery The new battery value of the Robot.
    */
   void setBattery(int battery);
   /**
    * @brief getConsumedEnergy A getter for the sum of the total consumed energy by this robot during the Simulation.
    * @return The sum of the consumed energy as an integer.
    */
   int getConsumedEnergy();
   void incrementConsumedEnergy();

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


};

#endif // ROBOT_H
