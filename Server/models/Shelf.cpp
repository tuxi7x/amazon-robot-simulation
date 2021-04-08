#include "Shelf.h"
#include <algorithm>

Shelf::Shelf(QObject *parent) : QObject(parent)
{

}

Shelf::Shelf(int row, int col) {
    _row = row;
    _col = col;
    _originalRow = row;
    _originalCol = col;
    _isAvailable = true;
}

int Shelf::getRow() {
    return _row;
}

int Shelf::getCol() {
    return _col;
}

int Shelf::getOriginalRow() const
{
    return _originalRow;
}

int Shelf::getOriginalCol() const
{
    return _originalCol;
}

void Shelf::setRow(int row)
{
    _row = row;
}

void Shelf::setCol(int col)
{
    _col = col;
}

bool Shelf::getIsAvailable() const
{
    return _isAvailable;
}

void Shelf::setIsAvailable(bool isAvailable)
{
    _isAvailable = isAvailable;
}

