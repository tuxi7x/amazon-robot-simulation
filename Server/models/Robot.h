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
   Robot(int row, int col, int direction);

private:
    int _id;
    int _row;
    int _col;
    int _direction;
    int _battery;
    int _destinationIndex;
    Shelf* _currentShelf;
    Product* _currentProduct;

    static int _idCounter;


signals:

};

#endif // ROBOT_H
