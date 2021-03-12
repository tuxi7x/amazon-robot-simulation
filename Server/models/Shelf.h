#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include "QVector"
#include "models/Product.h"

class Shelf : public QObject
{
    Q_OBJECT
public:
    explicit Shelf(QObject *parent = nullptr);

private:
    int _id;
    int _index;
    QVector<Product> _products;
    bool _isMoving;

signals:

};

#endif // SHELF_H
