#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
#include <QString>



class ProductModel
{
public:
    ProductModel(int id, QString name);

    QString getName() const;
    int getId() const;

private:
    int _id;
    QString _name;
};

#endif // PRODUCTMODEL_H
