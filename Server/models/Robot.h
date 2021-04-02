#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QStack>
#include "models/Shelf.h"
#include "models/Product.h"
#include "PathNode.h"

class Robot : public QObject
{
    Q_OBJECT
public:
   explicit Robot(QObject *parent = nullptr);
   Robot(int row, int col, int direction);

   int getRow();
   int getCol();
   int getDirection();
   int getBattery();
   void pushToPath(PathNode* x);
   bool pathIsEmpty();
   void stepOnPath();


private:
   int _id;
   int _row;
   int _col;
   int _direction;
   int _battery;
   Shelf* _currentShelf;
   Product* _currentProduct;
   QStack<PathNode*> _robotPath;

   static int _idCounter;


signals:

};

#endif // ROBOT_H
