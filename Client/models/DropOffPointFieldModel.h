#ifndef DROPOFFPOINTFIELDMODEL_H
#define DROPOFFPOINTFIELDMODEL_H

#include <QObject>
#include <QJsonObject>


/**
 * @brief The DropOffPointFieldModel class contains the neccesary information about a Drop off point for the editor and for the simulation.
 */
class DropOffPointFieldModel: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief DropOffPointFieldModel The constructor for this Class.
     * @param row The row of the Docker
     * @param col The column of the Docker
     * @param product The name of the product delivered to this drop off point.
     * @param parent The parent of this drop off point. as an optional parameter.
     */
    DropOffPointFieldModel(int row, int col, QString product, QObject* parent = nullptr);
    /**
     * @brief getProduct point Gets the name of the Product delivered to this drop off point
     * @return The name of the Product as a QString
     */
    QString getProduct() const;
    /**
     * @brief getRow A getter for the row of this Drop off point on the grid.
     * @return The row of the Drop off point
     */
    int getRow() const;
    /**
     * @brief getCol A getter for the column of this Drop off point on the grid.
     * @return The column of the Drop off point.
     */
    int getCol() const;
    /**
     * @brief write Writes the information about this Drop off point to the QJsonObject given as a parameter.
     * @param json The QJsonObject written into.
     */
    void write(QJsonObject &json);
    /**
     * @brief read Reads the information about this Drop off point from the QJsonObject given as a parameter.
     * @param json The QJsonObject read from.
     */
    void read(const QJsonObject &json);

private:
    int _row;
    int _col;
    QString _product;
};

#endif // DROPOFFPOINTFIELDMODEL_H
