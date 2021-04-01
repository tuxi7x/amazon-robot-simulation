#include "Product.h"

Product::Product(QObject *parent) : QObject(parent)
{

}

Product::Product(QString name, int shelf)
{
    _name = name;
    _shelf = shelf;
}


int Product::getShelf() {
    return _shelf;
}

QString Product::getName() {
    return _name;
}
