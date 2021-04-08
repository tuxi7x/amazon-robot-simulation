#include "Robot.h"
#include <QDebug>


int Robot::_idCounter = 1;

Robot::Robot(QObject *parent) : QObject(parent)
{

}

Robot::Robot(int row, int col, int direction)
{
    _id = _idCounter++;
    _row = row;
    _originalRow = row;
    _col = col;
    _originalCol = col;
    _direction = direction;
    _battery = 100;
    _maxBattery = 100;
    _state = FREE;
    _currentShelf = nullptr;
    _currentProduct = nullptr;
}

int Robot::getRow() {
    return _row;
}

int Robot::getCol() {
    return _col;
}

int Robot::getDirection() {
    return _direction;
}

int Robot::getBattery() {
    return _battery;
}

void Robot::pushToPath(PathNode *x)
{
    _robotPath.push(x);
}

bool Robot::pathIsEmpty()
{
    return _robotPath.isEmpty();
}

PathNode* Robot::stepOnPath()
{
    if(pathIsEmpty()) return nullptr;
    PathNode* next = _robotPath.pop();
    _row = next->getRow();
    _col = next->getCol();
    _direction = next->getOrientation();
    _battery--;
    if(_currentShelf != nullptr) {
     _currentShelf->setRow(next->getRow());
     _currentShelf->setCol(next->getCol());
    }
    return next;
}

int Robot::getOriginalRow() const
{
    return _originalRow;
}

int Robot::getOriginalCol() const
{
    return _originalCol;
}

RobotStates Robot::getState() const
{
    return _state;
}

void Robot::setState(const RobotStates &state)
{
    _state = state;
}

void Robot::setCurrentShelf(Shelf *currentShelf)
{
    _currentShelf = currentShelf;
}

int Robot::getMaxBattery() const
{
    return _maxBattery;
}

Product *Robot::getCurrentProduct() const
{
    return _currentProduct;
}

void Robot::setCurrentProduct(Product *currentProduct)
{
    _currentProduct = currentProduct;
}

void Robot::clearPath()
{
    _robotPath.clear();
}

Shelf *Robot::getCurrentShelf() const
{
    return _currentShelf;
}

void Robot::setBattery(int battery)
{
    _battery = battery;
}


