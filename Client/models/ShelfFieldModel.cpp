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
