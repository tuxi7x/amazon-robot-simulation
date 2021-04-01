#ifndef DROPOFFPOINT_H
#define DROPOFFPOINT_H

#include <QObject>

class DropOffPoint : public QObject
{
    Q_OBJECT
public:
    explicit DropOffPoint(QObject *parent = nullptr);
    DropOffPoint(int row, int col, QString product);

    int getRow();
    int getCol();
    QString getProduct();

private:
    int _row;
    int _col;
    QString _product;

signals:

};

#endif // DROPOFFPOINT_H
