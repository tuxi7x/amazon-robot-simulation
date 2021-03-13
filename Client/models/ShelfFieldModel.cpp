#include "ShelfFieldModel.h"

ShelfFieldModel::ShelfFieldModel(int row, int col, QObject* parent): QObject(parent), _row(row), _col(col)
{

}



int ShelfFieldModel::getRow() const
{
    return _row;
}

int ShelfFieldModel::getCol() const
{
    return _col;
}

void ShelfFieldModel::write(QJsonObject &json) {
    json["row"] = _row;
    json["col"] = _col;
}

void ShelfFieldModel::read(const QJsonObject &json) {
    _row = json["row"].toInt();
    _col = json["col"].toInt();
}

void ShelfFieldModel::setRow(int row)
{
    _row = row;
}

void ShelfFieldModel::setCol(int col)
{
    _col = col;
}



