#include "Controller.h"
#include <cmath>
#include <algorithm>

Controller::Controller(QObject *parent) : QObject(parent)
{
    _speed = 1;
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
    planPathForRobot(_robots[0],5,5);
    planPathForRobot(_robots[1],0,5);
    _timer->start();
    _elapsedTime = 0;

}

void Controller::stopSimulation() {

}

void Controller::pauseSimulation() {

    _timer->stop();
}

void Controller::resumeSimulation() {

    _timer->start();
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
        if(orientation == 0 && row > 0 && fieldIsEmpty(row-1,col) && !_timeTable.contains(PathNode(row-1,col,orientation,time+1)) && !_timeTable.contains(PathNode(row-1,col,orientation,time+2))) {
            neighbours.push_back(new PathNode(row-1,col,orientation,time+1,currentNode));
        } else if(orientation == 1 && col < _size-1 && fieldIsEmpty(row,col+1) && !_timeTable.contains(PathNode(row,col+1,orientation,time+1)) && !_timeTable.contains(PathNode(row,col+1,orientation,time+2))) {
            neighbours.push_back(new PathNode(row,col+1,orientation,time+1,currentNode));
        } else if(orientation == 2 && row < _size-1 && fieldIsEmpty(row+1,col) && !_timeTable.contains(PathNode(row+1,col,orientation,time+1)) && !_timeTable.contains(PathNode(row+1,col,orientation,time+2))) {
            neighbours.push_back(new PathNode(row+1,col,orientation,time+1,currentNode));
        } else if(orientation == 3 && col > 0 && fieldIsEmpty(row,col-1) && !_timeTable.contains(PathNode(row,col-1,orientation,time+1)) && !_timeTable.contains(PathNode(row,col-1,orientation,time+2))) {
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

bool Controller::fieldIsEmpty(int row, int col)
{
    for(Docker*  d : _dockers) {
        if(d->getCol() == col && d->getRow() == row) return false;
    } for (DropOffPoint* d : _dropOffPoints) {
        if(d->getCol() == col && d->getRow() == row) return false;
    } for(Shelf* s : _shelves) {
        if(s->getCol() == col && s->getRow() == row) return false;
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

void Controller::tickHandler()
{

    _elapsedTime++;
    for(Robot* r : _robots) {
        r->stepOnPath();
    }
    updateState();
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


