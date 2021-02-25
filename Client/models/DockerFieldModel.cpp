#include "DockerFieldModel.h"

DockerFieldModel::DockerFieldModel(int row, int col): _row(row), _col(col)
{

}

int DockerFieldModel::getRow() const
{
    return _row;
}

int DockerFieldModel::getCol() const
{
    return _col;
}
