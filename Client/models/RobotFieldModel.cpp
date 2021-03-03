#include "RobotFieldModel.h"

RobotFieldModel::RobotFieldModel(int row, int col, int orientation, QObject* parent): QObject(parent), _row(row), _col(col), _orientation(orientation)
{

}



int RobotFieldModel::getRow() const
{
    return _row;
}

int RobotFieldModel::getCol() const
{
    return _col;
}

int RobotFieldModel::getOrientation() const
{
    return _orientation;
}

