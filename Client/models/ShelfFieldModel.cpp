#include "ShelfFieldModel.h"

ShelfFieldModel::ShelfFieldModel(int row, int col): _row(row), _col(col)
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
