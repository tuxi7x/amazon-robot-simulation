#include "DropOffPoint.h"

DropOffPoint::DropOffPoint(QObject *parent) : QObject(parent)
{

}

DropOffPoint::DropOffPoint(int row, int col, QString product) {
    _row = row;
    _col = col;
    _product = product;
}

int DropOffPoint::getRow() {
    return _row;
}

int DropOffPoint::getCol() {
    return _col;
}

QString DropOffPoint::getProduct() {
    return _product;
}
