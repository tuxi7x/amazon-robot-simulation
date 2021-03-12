#include "Robot.h"

Robot::Robot(QObject *parent) : QObject(parent)
{

}

Robot::Robot(int id, int index, int direction, int battery)
{
    _id = id;
    _index = index;
    _direction = direction;
    _battery = battery;
}
