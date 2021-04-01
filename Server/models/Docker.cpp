#include "Docker.h"

Docker::Docker(QObject *parent) : QObject(parent)
{

}

Docker::Docker(int row, int col) {
    _row = row;
    _col = col;
}

int Docker::getRow() {
    return _row;
}

int Docker::getCol() {
    return _col;
}
