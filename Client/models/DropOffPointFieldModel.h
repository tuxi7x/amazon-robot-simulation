#ifndef DROPOFFPOINTFIELDMODEL_H
#define DROPOFFPOINTFIELDMODEL_H

#include <QObject>
#include <QJsonObject>



class DropOffPointFieldModel: public QObject
{
    Q_OBJECT
public:
    DropOffPointFieldModel(int row, int col, QString product, QObject* parent = nullptr);

    QString getProduct() const;
    int getCol() const;
    int getRow() const;

    void write(QJsonObject &json);
    void read(const QJsonObject &json);

private:
    int _row;
    int _col;
    QString _product;
};

#endif // DROPOFFPOINTFIELDMODEL_H
