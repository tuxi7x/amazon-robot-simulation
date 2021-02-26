#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
#include <QObject>
#include <QString>



class ProductModel: public QObject
{
    Q_OBJECT
public:
    ProductModel(int id, QString name, QObject* parent = nullptr);

    QString getName() const;
    int getId() const;

private:
    int _id;
    QString _name;
};

#endif // PRODUCTMODEL_H
