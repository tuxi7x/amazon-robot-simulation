#include "Controller.h"
#include <cmath>
#include <algorithm>

Controller::Controller(QObject *parent) : QObject(parent)
{
    _speed = 1;
    _paused = false;
    _elapsedTime = 0;
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    connect(_timer, SIGNAL(timeout()), this, SLOT(tickHandler()));
}

void Controller::addRobot(int row, int col, int orientation) {
    _robots.append(new Robot(row, col, orientation));
}

void Controller::addProduct(QString name, int shelf) {
    _products.append(new Product(name, shelf));
}

void Controller::addDocker(int row, int col) {
    _dockers.append(new Docker(row, col));
}

void Controller::addDropOffPoint(int row, int col, QString product) {
    _dropOffPoints.append(new DropOffPoint(row, col, product));
}

void Controller::addOrder(QString name) {
    _orders.append(name);
}

void Controller::addShelf(int row, int col) {
    _shelves.append(new Shelf(row, col));
}

void Controller::setSize(int size) {
    _size = size;
}

void Controller::setSpeed(int speed) {
    _speed = speed;
}

void Controller::startSimulation() {
    _timer->start();
    _elapsedTime = 0;

}

void Controller::stopSimulation() {

}

void Controller::pauseSimulation() {

    _timer->stop();
    _paused = true;
}

void Controller::resumeSimulation() {
    _timer->start();
    _paused = false;
}

bool Controller::getPaused()
{
    return _paused;
}

bool Controller::planPathForRobot(Robot *r, int destinationRow, int destinationCol)
{
    _timer->stop();
    int startRow = r->getRow();
    int startCol = r->getCol();
    int startOrientation = r->getDirection();
    int startTime = _elapsedTime;

    PathNode* startNode = new PathNode(startRow,startCol,startOrientation,startTime);
    startNode->setGValue(0);
    startNode->setHValue(calculateHeuristicValue(startRow,startCol,destinationRow,destinationCol));

    QVector<PathNode*> openSet;
    QVector<PathNode*> closedSet;
    openSet.append(startNode);

    while(!openSet.isEmpty()) {
        std::sort(openSet.begin(),openSet.end(),[](PathNode* a, PathNode* b){return a->fValue() > b->fValue();});
        PathNode* currentNode = openSet.takeLast();

        //Generate the neighbours of the current node.
        QVector<PathNode*> neighbours;
        int row = currentNode->getRow();
        int col = currentNode->getCol();
        int time = currentNode->getTime();
        int orientation = currentNode->getOrientation();
        if(orientation == 0 && row > 0 && fieldIsValid(row-1,col,r,destinationRow,destinationCol) && !_timeTable.contains(PathNode(row-1,col,orientation,time+1)) && !_timeTable.contains(PathNode(row-1,col,orientation,time+2))) {
            neighbours.push_back(new PathNode(row-1,col,orientation,time+1,currentNode));
        } else if(orientation == 1 && col < _size-1 && fieldIsValid(row,col+1,r,destinationRow,destinationCol) && !_timeTable.contains(PathNode(row,col+1,orientation,time+1)) && !_timeTable.contains(PathNode(row,col+1,orientation,time+2))) {
            neighbours.push_back(new PathNode(row,col+1,orientation,time+1,currentNode));
        } else if(orientation == 2 && row < _size-1 && fieldIsValid(row+1,col,r,destinationRow,destinationCol) && !_timeTable.contains(PathNode(row+1,col,orientation,time+1)) && !_timeTable.contains(PathNode(row+1,col,orientation,time+2))) {
            neighbours.push_back(new PathNode(row+1,col,orientation,time+1,currentNode));
        } else if(orientation == 3 && col > 0 && fieldIsValid(row,col-1,r,destinationRow,destinationCol) && !_timeTable.contains(PathNode(row,col-1,orientation,time+1)) && !_timeTable.contains(PathNode(row,col-1,orientation,time+2))) {
            neighbours.push_back(new PathNode(row,col-1,orientation,time+1,currentNode));
        }
        if(!_timeTable.contains(PathNode(row,col,nextOrientation(orientation),time+1)) && !_timeTable.contains(PathNode(row,col,nextOrientation(orientation),time+2))) {
            neighbours.push_back(new PathNode(row,col,nextOrientation(orientation),time+1,currentNode));
        }
        if(!_timeTable.contains(PathNode(row,col,prevOrientation(orientation),time+1)) && !_timeTable.contains(PathNode(row,col,prevOrientation(orientation),time+2))) {
            neighbours.push_back(new PathNode(row,col,prevOrientation(orientation),time+1,currentNode));
        }
        if(_timeTable.contains(PathNode(row,col,orientation,time+1)) && _timeTable.contains(PathNode(row,col,orientation,time+2))) {
            neighbours.push_back(new PathNode(row,col,orientation,time+1,currentNode));
        }

        for(PathNode* neighbour : neighbours) {
            if(neighbour->getRow() == destinationRow && neighbour->getCol() == destinationCol) {
                r->clearPath();
                while(neighbour != nullptr) {
                    r->pushToPath(neighbour);
                    _timeTable.insert(PathNode(neighbour->getRow(),neighbour->getCol(),neighbour->getOrientation(),neighbour->getTime()));
                    neighbour = neighbour->getParent();
                }
                _timer->start();
                return true;
            }
            neighbour->setGValue(currentNode->getGValue() + calculateGValue(row,col,neighbour->getRow(),neighbour->getCol(),time,neighbour->getTime()));
            neighbour->setHValue(calculateHeuristicValue(neighbour->getRow(),neighbour->getCol(),destinationRow,destinationCol));

            if(std::find_if(openSet.begin(),openSet.end(),[=](PathNode* a){return a->getRow() == neighbour->getRow() && a->getCol() == neighbour->getCol()
            && a->getOrientation() == neighbour->getOrientation() && a->fValue() < neighbour->fValue();}) != openSet.end()) {
                continue;
            }

            if(std::find_if(closedSet.begin(),closedSet.end(),[=](PathNode* a){return a->getRow() == neighbour->getRow() && a->getCol() == neighbour->getCol()
            &&  a->getOrientation() == neighbour->getOrientation() && a->fValue() < neighbour->fValue();}) != closedSet.end()) {
                continue;
            }
            openSet.push_back(neighbour);
        }
    closedSet.push_back(currentNode);
    }
    _timer->start();
    return false;
}

int Controller::calculateHeuristicValue(int startX, int startY, int goalX, int goalY)
{
    return abs(startX-goalX) + abs(startY-goalY);
}

int Controller::calculateGValue(int startX, int startY, int goalX, int goalY, int startTime, int goalTime)
{
    return abs(startX-goalX) + abs(startY-goalY) + abs (startTime-goalTime);
}

bool Controller::fieldIsValid(int row, int col, Robot *r, int goalRow, int goalCol)
{
    if(row == goalRow && col == goalCol) return true;
    for(Docker*  d : _dockers) {
        if(d->getCol() == col && d->getRow() == row) return false;
    } for (DropOffPoint* d : _dropOffPoints) {
        if(d->getCol() == col && d->getRow() == row) return false;
    } for(Shelf* s : _shelves) {
        if(s->getCol() == col && s->getRow() == row && r->getCurrentShelf() != nullptr) return false;
    }
    return true;
}

int Controller::nextOrientation(int orientation)
{
    return (orientation+1)%4;
}

int Controller::prevOrientation(int orientation)
{
    return (orientation-1)%4;
}

Shelf *Controller::getShelfWithPosition(int row, int col)
{
    for(Shelf* s : _shelves) {
        if(s->getRow() == row && s->getCol() == col) return s;
    }
    return nullptr;
}

DropOffPoint *Controller::getDropOffPointForProduct(QString product)
{
    for(DropOffPoint* d: _dropOffPoints)  {
        if(d->getProduct() == product) return d;
    }
    return nullptr;
}

Docker *Controller::getNearestDocker(Robot *r)
{
    Docker* item = _dockers[0];
    int min = calculateHeuristicValue(r->getRow(),r->getCol(),item->getRow(),item->getCol());
    for(Docker* d : _dockers) {
        int val = calculateHeuristicValue(r->getRow(),r->getCol(),d->getRow(),d->getCol());
        if(val < min) {
            item = d;
            min = val;
        }
    }
    return item;
}

void Controller::removeProduct(Product *p)
{
    _products.erase(std::find(_products.begin(),_products.end(),p));
}

Product *Controller::getProductWithName(QString product)
{
    for(Product* p : _products) {
        if(p->getName() == product && _shelves[p->getShelf()]->getIsAvailable()) return p;
    }
    return nullptr;
}


Robot *Controller::getRobotNearestToShelf(Shelf *s)
{
    bool l = false;
    Robot* item;
    int min;
    for(Robot* r : _robots) {
        int val = calculateHeuristicValue(r->getRow(),r->getCol(),s->getRow(),s->getCol());
        if(!l && r->getState() == FREE) {
            l = true;
            item = r;
            min = val;
        }
        else if (l && r->getState() == FREE && min > val) {
            item = r;
            min = val;
        }
    }
    return l ? item : nullptr;
}

void Controller::tickHandler()
{

    _elapsedTime++;
    //Step with robots using their Route stack
    for(Robot* r : _robots) {
        qInfo() << r->getState();
        PathNode *n = r->stepOnPath();
        if(n!= nullptr ) {
            _timeTable.remove(PathNode(n->getRow(),n->getCol(),n->getOrientation(),n->getTime()));
        } else {
            if(r->getState() == FREE) continue;
            else if (r->getState() == GOINGFORSHELF) {
                Shelf* s = getShelfWithPosition(r->getRow(),r->getCol());
                r->setCurrentShelf(s);
                DropOffPoint* d = getDropOffPointForProduct(r->getCurrentProduct()->getName());
                qInfo() << d->getRow() << " " <<  d->getCol();
                if(planPathForRobot(r,d->getRow(),d->getCol())) {
                    r->setState(TAKINGSHELF);
                }
            } else if (r->getState() == TAKINGSHELF) {
                removeProduct(r->getCurrentProduct());
                delete r->getCurrentProduct();
                r->setCurrentProduct(nullptr);
                if(planPathForRobot(r,r->getCurrentShelf()->getOriginalRow(),r->getCurrentShelf()->getOriginalCol())) {
                    r->setState(TAKINGSHELFBACK);
                }
            } else if (r->getState() == TAKINGSHELFBACK) {
                r->getCurrentShelf()->setIsAvailable(true);
                r->setCurrentShelf(nullptr);
                if(r->getBattery() <= r->getMaxBattery()/2) {
                    Docker* d = getNearestDocker(r);
                    if(planPathForRobot(r,d->getRow(),d->getCol())) {
                        r->setState(GOINGTOCHARGER);
                    }
                } else {
                    r->setState(FREE);
                    planPathForRobot(r,r->getOriginalRow(),r->getOriginalCol());
                }
            } else if (r->getState() == GOINGTOCHARGER) {
                r->setState(CHARGING);
            } else if (r->getState() == CHARGING) {
                r->setState(FREE);
                r->setBattery(r->getMaxBattery());
                planPathForRobot(r,r->getOriginalRow(),r->getOriginalCol());
            }
        }
    }
    //Assigning the nearest free robot to current orders
    QVector<QString> deletable;

    for(QString& order : _orders) {
        Product* p = getProductWithName(order);
        if(p == nullptr) continue;
        Shelf * s = _shelves[p->getShelf()];
        Robot* r = getRobotNearestToShelf(s);
        if(r == nullptr) continue;
        if(planPathForRobot(r,s->getRow(),s->getCol())) {
            s->setIsAvailable(false);
            r->setState(GOINGFORSHELF);
            r->setCurrentProduct(p);
            deletable.append(order);
        }
    }
    for(QString& d : deletable) {
        _orders.erase(std::find(_orders.begin(),_orders.end(),d));
    }


    emit updateState();
}

int Controller::getSize() {
    return _size;
}

int Controller::getSpeed() {
    return _speed;
}

QVector<Robot*> Controller::getRobots() {
    return _robots;
}

QVector<Docker*> Controller::getDockers() {
    return _dockers;
}

QVector<DropOffPoint*> Controller::getDropOffPoints() {
    return _dropOffPoints;
}

QVector<Shelf*> Controller::getShelves() {
    return _shelves;
}

QVector<QString> Controller::getOrders() {
    return _orders;
}

QVector<Product*> Controller::getProducts() {
    return _products;
}


