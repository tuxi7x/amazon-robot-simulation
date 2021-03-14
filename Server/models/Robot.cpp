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

