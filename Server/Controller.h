#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include "models/Robot.h"
#include "models/Docker.h"
#include "models/DropOffPoint.h"
#include "models/Product.h"
#include "models/Shelf.h"
#include <QTimer>



class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

private:
    QVector<Robot*> _robots;
    QVector<Docker*> _dockers;
    QVector<DropOffPoint*> _dropOffPoints;
    QVector<Shelf*> _shelves;
    QVector<Product*> _products;
    QVector<QString> _orders;


signals:

};

#endif // CONTROLLER_H
