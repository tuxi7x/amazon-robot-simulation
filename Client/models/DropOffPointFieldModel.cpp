#include "DropOffPointFieldModel.h"

DropOffPointFieldModel::DropOffPointFieldModel(int row, int col, int product): _row(row), _col(col), _product(product)
{

}

int DropOffPointFieldModel::getProduct() const
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
