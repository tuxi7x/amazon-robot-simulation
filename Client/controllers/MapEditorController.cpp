#include "MapEditorController.h"

MapEditorController::MapEditorController(QObject *parent) : QObject(parent)
{

}

void MapEditorController::createNewMap(int size)
{
    _size = size;
    _robots.clear();
    _shelves.clear();
    _dockers.clear();
    _dropOffPoints.clear();
    _products.clear();

    emit mapCreated();

}

QPair<MapEditorController::FieldTypes, QObject*> MapEditorController::getField(int row, int col)
{
    for(int i=0; i<_robots.count();i++) {
        if(_robots[i]->getRow() == row && _robots[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(Robot, _robots[i]);
        }
    }

    for(int i=0; i<_dockers.count(); i++) {
        if(_dockers[i]->getRow() == row && _dockers[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(Docker, _dockers[i]);
        }
    }

    for(int i=0; i<_shelves.count();i++) {
        if(_shelves[i]->getRow() == row && _shelves[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(Shelf, _shelves[i]);
        }
    }

    for(int i=0; i<_dropOffPoints.count();i++) {
        if(_dropOffPoints[i]->getRow() == row && _dropOffPoints[i]->getCol() == col) {
            return QPair<FieldTypes, QObject*>(DropOffPoint, _dropOffPoints[i]);
        }
    }

    return QPair<FieldTypes,QObject*> (Empty,nullptr);
}

int MapEditorController::getSize()
{
    return _size;
}

void MapEditorController::addRobot(int row, int col)
{
    if(getField(row,col).first == Empty) {
        _robots.append(new RobotFieldModel(row,col,0));
        emit fieldChanged(row,col);
    }
}

void MapEditorController::addShelf(int row, int col)
{
    if(getField(row,col).first == Empty) {
        _shelves.append(new ShelfFieldModel(row,col));
        emit fieldChanged(row,col);
    }
}

void MapEditorController::addDocker(int row, int col)
{
    if(getField(row,col).first == Empty) {
        _dockers.append(new DockerFieldModel(row,col));
        emit fieldChanged(row,col);
    }
}

void MapEditorController::addDropOffPoint(int row, int col)
{
    if(getField(row,col).first == Empty) {
        _dropOffPoints.append(new DropOffPointFieldModel(row,col,0)); //TODO implement dialog in map editor to bind drop off point to a product
        emit fieldChanged(row,col);
    }
}

void MapEditorController::addProduct(int row, int col, QString productName)
{
    // TODO implement this
}
