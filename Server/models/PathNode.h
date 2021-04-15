#ifndef PATHNODE_H
#define PATHNODE_H
#include <qhashfunctions.h>
#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using qhash_result_t = uint;
#else
using qhash_result_t = size_t;
#endif


class PathNode
{
public:
    PathNode();
    PathNode(int row, int col, int orientation, int time, PathNode* parent = nullptr);
    //The f value is the sum of the g and h values.
    int fValue();
    int getRow() const;
    int getCol() const;
    int getOrientation() const;
    int getTime() const;
    PathNode *getParent() const;

    void setGValue(int gValue);
    void setHValue(int hValue);

    int getGValue() const;

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
