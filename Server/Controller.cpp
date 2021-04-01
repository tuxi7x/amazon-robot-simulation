#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    _speed = 1;
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
    qInfo() << "sim started";
}

void Controller::stopSimulation() {

}

void Controller::pauseSimulation() {

}

void Controller::resumeSimulation() {

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


