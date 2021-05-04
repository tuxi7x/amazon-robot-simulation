#ifndef PATHNODE_H
#define PATHNODE_H

#include <qhashfunctions.h>
#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using qhash_result_t = uint;
#else
using qhash_result_t = size_t;
#endif

class Robot;


/**
 * @brief The PathNode class is used by the multi agent pathfinding algorithm. It contains all
 * the necessary information about the steps that the robot has to take. It is also used
 * by the timetable in the controller, to determine whether a node is free at a given time.
 */
class PathNode
{
public:
    /**
     * @brief PathNode Default constructor for the PathNode class.
     */
    PathNode();
    /**
     * @brief PathNode A constructor for Pathnode which takes all the necessary information about a node as parameter.
     * @param row The y coordinate of the node in the warehouse.
     * @param col The x coordinate of the node in the warehouse
     * @param orientation The direction in which the robot will be facing when stepping on this node.
     * @param time The time elapsed since the start of the simulation when the robot will step on this node.
     * @param parent Optional parameter, it is used to access the node before this one in the robot's path. The default value is NULL.
     * @param reserver Optional parameter: we can give the robot that reserved this node in the TimeTable
     */
    PathNode(int row, int col, int orientation, int time, PathNode *parent = nullptr, Robot *reserver = nullptr);
    /**
     * @brief getter for the f value of this node. The f value is used by A* algorithm to rank nodes.
     * @return the f value of this node.
     */
    int fValue();
    /**
     * @brief getRow getter for the y position of this node in the warehouse.
     * @return the y position as an integer.
     */
    int getRow() const;
    /**
     * @brief getRow getter for the x position of this node in the warehouse.
     * @return the x position as an integer.
     */
    int getCol() const;
    /**
     * @brief getOrientation returns the direction in which the robot will be facing when stepping on this node.
     * 0 = north, 1 = east, 2 = south, 3 = west.
     * @return The orientation as an integer between 1 and 3.
     */
    int getOrientation() const;
    /**
     * @brief getTime return the time elapsed since the start of the simulation when the robot will be stepping on this node.
     * @return the time elapsed as an integer.
     */
    int getTime() const;
    /**
     * @brief getParent A getter for the parent of this node. The parent of this node is the node before this one in the robot's path.
     * @return Returns a PathNode pointer that refers to the parent of this node. It can return null if this node has no parent.
     */
    PathNode *getParent() const;

    /**
     * @brief A setter for the G value of this node, used by the A* algorithm.
     * @param gValue the new G value.
     */
    void setGValue(int gValue);
    /**
     * @brief A setter for the H value of this node, used by the A* algorithm.
     * @param hValue the new H value
     */
    void setHValue(int hValue);
    /**
     * @brief A getter for the G value of this node, used by the A* algorithm.
     * @return The H value of this node as an integer.
     */
    int getGValue() const;

    Robot *getReserver() const;

private:
    int _row;
    int _col;
    int _orientation;
    int _time;
    //The g value represents the distance between the starting point and this node.
    int _gValue;
    //the h value represents an estimate of the distance between the starting point and this node.
    int _hValue;
    PathNode* _parent;
    Robot* _reserver;
};


inline bool operator== (const PathNode& a, const PathNode& b)
{
    //Two nodes are considered equal if they are in the same position in the same time.
    return a.getRow() == b.getRow() && a.getCol() == b.getCol() && a.getTime() == b.getTime();
}


inline qhash_result_t qHash (const PathNode& a, const qhash_result_t& seed)
{
    qhash_result_t newSeed = seed;
    QtPrivate::QHashCombine hash;
    newSeed = hash(newSeed,a.getCol());
    newSeed = hash(newSeed,a.getRow());
    newSeed = hash(newSeed,a.getTime());
    return newSeed;
}


#endif // PATHNODE_H
