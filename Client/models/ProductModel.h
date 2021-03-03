#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
#include <QObject>
#include <QString>



class ProductModel: public QObject
{
    Q_OBJECT
public:
    ProductModel(QString name, int shelf, QObject* parent = nullptr);

    QString getName() const;
    int getShelf() const;

private:
    QString _name;
    int _shelf;
};

#endif // PRODUCTMODEL_H
