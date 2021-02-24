#include "MapEditorController.h"

MapEditorController::MapEditorController(QObject *parent) : QObject(parent)
{

}

void MapEditorController::createNewMap(int size)
{
    _size = size;
    _field.clear();

    for(int i=0; i<_size;i++) {
        QVector<FieldTypes> row;
        for(int j=0; j<_size;j++) {
            row.append(Empty);
        }
        _field.append(row);
    }

    emit mapCreated();

}

MapEditorController::FieldTypes MapEditorController::getField(int row, int col)
{
    return _field[row][col];
}

int MapEditorController::getSize()
{
    return _size;
}

void MapEditorController::addRobot(int row, int col)
{
    _field[row][col] = Robot;
    fieldChanged(row,col);
}

void MapEditorController::addShelf(int row, int col)
{
    _field[row][col] = Shelf;
    fieldChanged(row,col);
}

void MapEditorController::addDocker(int row, int col)
{
    _field[row][col] = Docker;
    fieldChanged(row,col);
}

void MapEditorController::addDropOffPoint(int row, int col)
{
    _field[row][col] = DropOffPoint;
    fieldChanged(row,col);
}

void MapEditorController::addProduct(int row, int col, QString productName)
{
    // TODO implement this
}
