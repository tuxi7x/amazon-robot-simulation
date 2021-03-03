#include "ProductModel.h"

ProductModel::ProductModel(QString name, int shelf, QObject* parent): QObject(parent), _name(name), _shelf(shelf)
{

}



QString ProductModel::getName() const
{
    return _name;
}

int ProductModel::getShelf() const
{
    return _shelf;
}

