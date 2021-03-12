#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product : public QObject
{
    Q_OBJECT
public:
    explicit Product(QObject *parent = nullptr);
    Product(QString name);
    Product(int id, QString name);

private:
    int _id;
    QString _name;
    bool _requested;

signals:

};

#endif // PRODUCT_H
