#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

/**
 * @brief Model class containing information about a product
 */
class Product : public QObject
{
    Q_OBJECT
public:
    explicit Product(QObject* parent = nullptr);

    /**
     * @brief Product Constructor for Product class
     * @param name The name of the product
     * @param shelf The id of the shelf where the product is placed
     */
    Product(QString name, int shelf);

    /**
     * @brief getShelf Getter for the shelf id
     * @return The id of the shelf where the product is placed
     */
    int getShelf();

    /**
     * @brief getName Getter for the name of the product
     * @return The name of the product
     */
    QString getName();

private:
    int _shelf;
    QString _name;
    bool _requested;

signals:

};

#endif // PRODUCT_H
