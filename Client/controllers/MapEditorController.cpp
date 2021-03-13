#include "MapEditorController.h"

MapEditorController::MapEditorController(QObject *parent) : QObject(parent)
{

}

MapEditorController::~MapEditorController()
{
    std::for_each(_robots.begin(),_robots.end(),[](RobotFieldModel* r){delete r;});
    std::for_each(_shelves.begin(),_shelves.end(),[](ShelfFieldModel* s){delete s;});
    std::for_each(_dockers.begin(),_dockers.end(),[](DockerFieldModel* d){delete d;});
    std::for_each(_dropOffPoints.begin(),_dropOffPoints.end(),[](DropOffPointFieldModel* d){delete d;});
    std::for_each(_products.begin(),_products.end(),[](ProductModel* p){delete p;});
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
    _selectedShelves.clear();
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
    if(!_selectedShelves.contains(_shelves[i])) { //putting a product on a shelf that is not selected
        bool valid = true;
        for(int j = 0; j<_products.size();j++) {
            valid = valid && (_products[j]->getName() != productName || _products[j]->getShelf() != i);
        }

        if(!valid) return false;
        _products.append(new ProductModel(productName,i));
        return true;
    } else {
        bool valid = true;
        i = 0;
        while (i < _shelves.size() && valid)  {
            valid = std::find_if(_products.begin(),_products.end(), [&](ProductModel* p){
                 return _selectedShelves.contains(_shelves[i]) && p->getName() == productName && p->getShelf() == i;
            }) == _products.end();
            i++;
        }
        if(!valid) return false;
        for(int i=0; i<_shelves.size();i++) {
            if(_selectedShelves.contains(_shelves[i])) {
                _products.append(new ProductModel(productName,i));
            }
        }
        return true;
    }
}

bool MapEditorController::validateProductPlacement(int row, int col)
{
    return getField(row,col).first == Shelf;
}

bool MapEditorController::fieldIsEmpty()
{
    return _robots.isEmpty() && _dockers.isEmpty() && _shelves.isEmpty();
}

void MapEditorController::toggleShelfSelection(ShelfFieldModel *s)
{
    int pos = _selectedShelves.indexOf(s);
    if(pos == -1) {
         _selectedShelves.append(s);
    }
    else {
        _selectedShelves.removeAt(pos);
    }

    emit shelfSelectionChanged(s->getRow(),s->getCol(),pos == -1);
}

bool MapEditorController::moveSelectedShelves(int direction)
{
    //This is not fully correct yet. If there are 2 selected shelves next to eachother and we
    //want to move to the direction of the other shelf then it fails now.
    if(direction == 0) {
        bool l = true;
        int i = 0;
        while(l && i < _selectedShelves.size()) {
            ShelfFieldModel* s = _selectedShelves[i];
            l = s->getRow() > 0 && getField(s->getRow()-1,s->getCol()).first == Empty;
            if(!l && s->getRow() > 0) {
                QPair<FieldTypes, QObject*> p = getField(s->getRow()-1,s->getCol());
                if(p.first == Shelf) {
                    ShelfFieldModel* ns = qobject_cast<ShelfFieldModel*> (p.second);
                    l = isASelectedShelf(ns->getRow(),ns->getCol()) ? true : l;
                }
            }
            i++;
        }
        if(!l) return false;
        else {
            for(int i=0; i<_selectedShelves.size(); i++) {
                ShelfFieldModel* s = _selectedShelves[i];
                s->setRow(s->getRow()-1);
                emit fieldChanged(s->getRow()+1,s->getCol());
                emit fieldChanged(s->getRow(),s->getCol());
            }
            return  true;
        }

    } else if (direction == 1) {
        bool l = true;
        int i = 0;
        while(l && i <_selectedShelves.size()) {
            ShelfFieldModel* s = _selectedShelves[i];
            l = s->getCol() < _size-1 && getField(s->getRow(),s->getCol()+1).first == Empty;
            if(!l && s->getCol() < _size-1) {
                QPair<FieldTypes, QObject*> p = getField(s->getRow(),s->getCol()+1);
                if(p.first == Shelf) {
                    ShelfFieldModel* ns = qobject_cast<ShelfFieldModel*> (p.second);
                    l = isASelectedShelf(ns->getRow(),ns->getCol()) ? true : l;
                }
            }
            i++;
        }
        if(!l) return false;
        else {
            for(int i=0; i<_selectedShelves.size(); i++) {
                ShelfFieldModel* s = _selectedShelves[i];
                s->setCol(s->getCol()+1);
                emit fieldChanged(s->getRow(),s->getCol()-1);
                emit fieldChanged(s->getRow(),s->getCol());
            }
            return true;
        }

    } else if (direction == 2) {
        bool l = true;
        int i = 0;
        while(l && i <_selectedShelves.size()) {
            ShelfFieldModel* s = _selectedShelves[i];
            l = s->getRow() < _size-1 && getField(s->getRow()+1,s->getCol()).first == Empty;
            if(!l && s->getRow() < _size-1) {
                QPair<FieldTypes, QObject*> p = getField(s->getRow()+1,s->getCol());
                if(p.first == Shelf) {
                    ShelfFieldModel* ns = qobject_cast<ShelfFieldModel*> (p.second);
                    l = isASelectedShelf(ns->getRow(),ns->getCol()) ? true : l;
                }
            }
            i++;
        }
        if(!l) return false;
        for(int i=0; i<_selectedShelves.size(); i++) {
            ShelfFieldModel* s = _selectedShelves[i];
            s->setRow(s->getRow()+1);
            emit fieldChanged(s->getRow()-1,s->getCol());
            emit fieldChanged(s->getRow(),s->getCol());
        }
        return true;

    } else if (direction == 3) {
        bool l = true;
        int i = 0;
        while(l && i <_selectedShelves.size()) {
            ShelfFieldModel* s = _selectedShelves[i];
            l = s->getCol() > 0 && getField(s->getRow(),s->getCol()-1).first == Empty;
            if(!l && s->getCol() > 0) {
                QPair<FieldTypes, QObject*> p = getField(s->getRow(),s->getCol()-1);
                if(p.first == Shelf) {
                    ShelfFieldModel* ns = qobject_cast<ShelfFieldModel*> (p.second);
                    l = isASelectedShelf(ns->getRow(),ns->getCol()) ? true : l;
                }
            }
            i++;
        }
        if(!l) return false;
            for(int i=0; i<_selectedShelves.size(); i++) {
                ShelfFieldModel* s = _selectedShelves[i];
                s->setCol(s->getCol()-1);
                emit fieldChanged(s->getRow(),s->getCol()+1);
                emit fieldChanged(s->getRow(),s->getCol());
            }
            return true;
    }
    return false;
}

bool MapEditorController::isASelectedShelf(int row, int col)
{
    for(int i=0;i<_selectedShelves.size();i++) {
        if(_selectedShelves[i]->getRow() == row && _selectedShelves[i]->getCol() == col) return true;
    }
    return false;
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

QVector<QString> MapEditorController::getProducts()
{

    QVector<QString> l;

    for(int j=0; j<_products.size();j++) {
            l.append(_products[j]->getName());
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


    QJsonArray orderArray;
    foreach(QString order, _orders) {
        orderArray.append(order);
    }
    simulationObject["orders"] = orderArray;

    QJsonDocument saveDoc(simulationObject);
    file->write(saveDoc.toJson());
    file->close();

    return true;
}

QVector<QString> MapEditorController::getOrders() const
{
    return _orders;
}
void MapEditorController::setOrders(QVector<QString> orders)
{
    _orders.clear();
    for(int i = 0; i< orders.length(); i++){
        _orders.append(orders[i]);
    }
}
