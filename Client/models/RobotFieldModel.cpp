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

void RobotFieldModel::write(QJsonObject &json) {
    json["row"] = _row;
    json["col"] = _col;
    json["orientation"] = _orientation;
}

void RobotFieldModel::read(const QJsonObject &json) {
    _row = json["row"].toInt();
    _col = json["col"].toInt();
    _orientation = json["orientation"].toInt();
}


