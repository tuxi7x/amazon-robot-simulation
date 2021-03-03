#ifndef DROPOFFPOINTFIELDMODEL_H
#define DROPOFFPOINTFIELDMODEL_H

#include <QObject>



class DropOffPointFieldModel: public QObject
{
    Q_OBJECT
public:
    DropOffPointFieldModel(int row, int col, QString product, QObject* parent = nullptr);

    QString getProduct() const;
    int getCol() const;
    int getRow() const;

private:
    int _row;
    int _col;
    QString _product;
};

#endif // DROPOFFPOINTFIELDMODEL_H
