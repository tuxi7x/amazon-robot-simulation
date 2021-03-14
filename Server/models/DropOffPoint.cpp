#include "DropOffPoint.h"

DropOffPoint::DropOffPoint(QObject *parent) : QObject(parent)
{

}

DropOffPoint::DropOffPoint(int row, int col, QString product) {
    _row = row;
    _col = col;
    _product = product;
}
