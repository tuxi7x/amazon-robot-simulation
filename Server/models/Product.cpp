#include "Product.h"

Product::Product(QObject *parent) : QObject(parent)
{

}

Product::Product(QString name, int shelf)
{
    _name = name;
    _shelf = shelf;
}

