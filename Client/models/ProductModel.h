#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H
#include <QObject>
#include <QString>
#include <QJsonObject>


/**
 * @brief The ProductModel class contains the neccesary information about a product for the editor and for the simulation.
 */
class ProductModel: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ProductModel The constructor for this class
     * @param name The name of this product.
     * @param shelf The id of the shelf on which this product is on.
     * @param parent The parent of this product.
     */
    ProductModel(QString name, int shelf, QObject* parent = nullptr);
    /**
     * @brief getName A getter for the name of this product.
     * @return The name as a QString
     */
    QString getName() const;
    /**
     * @brief getShelf A getter for the id of the shelf on which this product is on.
     * @return The id of the shelf.
     */
    int getShelf() const;
    /**
     * @brief write Writes the information about this product to the QJsonObject given as a parameter.
     * @param json The QJsonObject written into.
     */
    void write(QJsonObject &json);
    /**
     * @brief read Reads the information about this product from the QJsonObject given as a parameter.
     * @param json The QJsonObject read from.
     */
    void read(const QJsonObject &json);

private:
    QString _name;
    int _shelf;
};

#endif // PRODUCTMODEL_H
