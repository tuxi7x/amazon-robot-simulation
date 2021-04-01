#include "Robot.h"


int Robot::_idCounter = 1;

Robot::Robot(QObject *parent) : QObject(parent)
{

}

Robot::Robot(int row, int col, int direction)
{
    _id = _idCounter++;
    _row = row;
    _col = col;
    _direction = direction;
    _battery = 100;
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
