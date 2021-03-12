#include "DropOffPointFieldModel.h"

DropOffPointFieldModel::DropOffPointFieldModel(int row, int col, QString product, QObject* parent): QObject(parent), _row(row), _col(col), _product(product)
{

}



QString DropOffPointFieldModel::getProduct() const
{
    return _product;
}

int DropOffPointFieldModel::getCol() const
{
    return _col;
}

int DropOffPointFieldModel::getRow() const
{
    return _row;
}

void DropOffPointFieldModel::write(QJsonObject &json) {
    json["row"] = _row;
    json["col"] = _col;
    json["product"] = _product;
}

void DropOffPointFieldModel::read(const QJsonObject &json) {
    _row = json["row"].toInt();
    _col = json["col"].toInt();
    _product = json["product"].toString();
}

