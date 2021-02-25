#include "ProductModel.h"

ProductModel::ProductModel(int id, QString name): _id(id), _name(name)
{

}

QString ProductModel::getName() const
{
    return _name;
}

int ProductModel::getId() const
{
    return _id;
}
