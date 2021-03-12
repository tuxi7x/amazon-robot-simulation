#include "Product.h"

Product::Product(QObject *parent) : QObject(parent)
{

}

Product::Product(QString name)
{
    _name = name;

}

Product::Product(int id, QString name)
{
    _id = id;
    _name = name;
}
