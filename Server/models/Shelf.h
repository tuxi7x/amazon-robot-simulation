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
    Shelf(int row, int col);

    int getRow();
    int getCol();
    int getOriginalRow() const;
    int getOriginalCol() const;
    void setRow(int row);
    void setCol(int col);

    bool getIsAvaliable() const;
    void setIsAvaliable(bool isAvaliable);

private:
    int _row;
    int _col;
    int _originalRow;
    int _originalCol;
    bool _isAvaliable;


signals:

};

#endif // SHELF_H
