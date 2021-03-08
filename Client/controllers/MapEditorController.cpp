#include "MapEditorController.h"

MapEditorController::MapEditorController(QObject *parent) : QObject(parent)
{

}

void MapEditorController::createNewMap(int size)
{
    std::for_each(_robots.begin(),_robots.end(),[](RobotFieldModel* r){delete r;});
    std::for_each(_shelves.begin(),_shelves.end(),[](ShelfFieldModel* s){delete s;});
    std::for_each(_dockers.begin(),_dockers.end(),[](DockerFieldModel* d){delete d;});
    std::for_each(_dropOffPoints.begin(),_dropOffPoints.end(),[](DropOffPointFieldModel* d){delete d;});
    std::for_each(_products.begin(),_products.end(),[](ProductModel* p){delete p;});

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

void MapEditorController::addDropOffPoint(int row, int col, QString product)
{
    if(getField(row,col).first == Empty) {
        _dropOffPoints.append(new DropOffPointFieldModel(row,col,product)); //TODO implement dialog in map editor to bind drop off point to a product
        emit fieldChanged(row,col);
    }
}

bool MapEditorController::addProduct(int row, int col, QString productName)
{
    int i = 0;
    while (i < _shelves.size() && !(_shelves[i]->getRow() == row && _shelves[i]->getCol() == col)) {
        i++;
    }
    bool valid = true;
    for(int j = 0; j<_products.size();j++) {
        valid = valid && (_products[j]->getName() != productName || _products[j]->getShelf() != i);
    }

    if(!valid) return false;
    _products.append(new ProductModel(productName,i));
    return true;

}

bool MapEditorController::validateProductPlacement(int row, int col)
{
    return getField(row,col).first == Shelf;
}

bool MapEditorController::fieldIsEmpty()
{
    return _robots.isEmpty() && _dockers.isEmpty() && _shelves.isEmpty();
}

QVector<QString> MapEditorController::getProductsOnShelf(int row, int col)
{
    int i = 0;
    while (i < _shelves.size() && !(_shelves[i]->getRow() == row && _shelves[i]->getCol() == col)) {
        i++;
    }
    QVector<QString> l;

    for(int j=0; j<_products.size();j++) {
        if(_products[j]->getShelf() == i) {
            l.append(_products[j]->getName());
        }
    }
    return l;
}

QVector<QString> MapEditorController::getUnassignedProducts()
{
    QVector<QString> l;

    for(int i=0; i<_products.size();i++) {
        if(!l.contains(_products[i]->getName())) {
            int j=0;
            while(j<_dropOffPoints.size() && _dropOffPoints[j]->getProduct() != _products[i]->getName()) j++;
            if(j == _dropOffPoints.size()) l.append(_products[i]->getName());
        }
    }
    return l;
}

QString MapEditorController::validateBeforeSave()
{
    if(_robots.isEmpty()) {
        return "Legalább egy robotot fel kell helyezni!";
    }else if(_shelves.isEmpty()) {
        return "Legalább egy polcot fel kell helyezni!";
    }else if(_products.isEmpty()) {
        return "Legalább egy terméket fel kell helyezni!";
    }else if(_dockers.isEmpty()) {
        return "Legalább egy töltőállomást fel kell helyezni!";
    }else if(_dropOffPoints.isEmpty()) {
        return "Legalább egy célállomást fel kell helyezni!";
    }else if (_products.length() != _dropOffPoints.length()){
        int tmp = _products.length()-_dropOffPoints.length();
    return "Még " + QString::number(tmp) + " célállomást fel kell helyezni!";
    }else return "OK";
}

bool MapEditorController::saveToJSON(QFile* file) {

    if (!file->open(QIODevice::WriteOnly)) {
            return false;
    }

    QJsonObject simulationObject;
    simulationObject["size"] = _size;

    QJsonArray robotArray;
        foreach (RobotFieldModel* robot, _robots) {
            QJsonObject robotObject;
            robot->write(robotObject);
            robotArray.append(robotObject);
        }
    simulationObject["robots"] = robotArray;

    QJsonArray shelfArray;
        foreach (ShelfFieldModel* shelf, _shelves) {
            QJsonObject shelfObject;
            shelf->write(shelfObject);
            shelfArray.append(shelfObject);
        }
    simulationObject["shelves"] = shelfArray;

    QJsonArray dockerArray;
        foreach (DockerFieldModel* docker, _dockers) {
            QJsonObject dockerObject;
            docker->write(dockerObject);
            dockerArray.append(dockerObject);
        }
    simulationObject["dockers"] = dockerArray;

    QJsonArray dropOffArray;
        foreach (DropOffPointFieldModel* dropOff, _dropOffPoints) {
            QJsonObject dropOffObject;
            dropOff->write(dropOffObject);
            dropOffArray.append(dropOffObject);
        }
    simulationObject["dropoffs"] = dropOffArray;

    QJsonArray productArray;
        foreach (ProductModel* product, _products) {
            QJsonObject productObject;
            product->write(productObject);
            productArray.append(productObject);
        }
    simulationObject["products"] = productArray;

    QJsonDocument saveDoc(simulationObject);
    file->write(saveDoc.toJson());
    file->close();

    return true;
}
