#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "models/Shelf.h"
#include "models/Product.h"

class Robot : public QObject
{
    Q_OBJECT
public:
   explicit Robot(QObject *parent = nullptr);
   Robot(int id, int index, int direction, int battery);

private:
    int _id;
    int _index;
    int _direction;
    int _battery;
    int _destinationIndex;
    Shelf* _currentShelf;
    Product* _currentProduct;


signals:

};

#endif // ROBOT_H
