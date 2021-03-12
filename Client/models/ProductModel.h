#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
#include <QObject>
#include <QString>
#include <QJsonObject>



class ProductModel: public QObject
{
    Q_OBJECT
public:
    ProductModel(QString name, int shelf, QObject* parent = nullptr);

    QString getName() const;
    int getShelf() const;

    void write(QJsonObject &json);
    void read(const QJsonObject &json);

private:
    QString _name;
    int _shelf;
};

#endif // PRODUCTMODEL_H
