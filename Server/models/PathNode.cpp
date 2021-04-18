#include "PathNode.h"

PathNode::PathNode()
{

}

PathNode::PathNode(int row, int col, int orientation, int time, PathNode *parent, Robot *reserver): _row(row), _col(col), _orientation(orientation), _time(time), _parent(parent), _reserver(reserver)
{

}

int PathNode::fValue()
{
    return _gValue + _hValue;
}

int PathNode::getRow() const
{
    return _row;
}

int PathNode::getCol() const
{
    return _col;
}

int PathNode::getOrientation() const
{
    return _orientation;
}


PathNode* PathNode::getParent() const
{
    return _parent;
}

void PathNode::setGValue(int gValue)
{
    _gValue = gValue;
}

void PathNode::setHValue(int hValue)
{
    _hValue = hValue;
}

int PathNode::getGValue() const
{
    return _gValue;
}

Robot *PathNode::getReserver() const
{
    return _reserver;
}

int PathNode::getTime() const
{
    return _time;
}
