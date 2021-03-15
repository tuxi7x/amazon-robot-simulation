#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

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
