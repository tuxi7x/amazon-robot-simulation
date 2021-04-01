#include "Shelf.h"

Shelf::Shelf(QObject *parent) : QObject(parent)
{

}

Shelf::Shelf(int row, int col) {
    _row = row;
    _col = col;
}

int Shelf::getRow() {
    return _row;
}

int Shelf::getCol() {
    return _col;
}
