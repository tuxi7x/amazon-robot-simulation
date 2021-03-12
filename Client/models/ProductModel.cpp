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

void ProductModel::write(QJsonObject &json) {
    json["name"] = _name;
    json["shelf"] = _shelf;
}

void ProductModel::read(const QJsonObject &json) {
    _name = json["name"].toString();
    _shelf = json["shelf"].toInt();
}


