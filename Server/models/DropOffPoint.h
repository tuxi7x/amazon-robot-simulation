#ifndef DROPOFFPOINT_H
#define DROPOFFPOINT_H

#include <QObject>

/**
 * @brief Model class containing information about a dropoff point
 */
class DropOffPoint : public QObject
{
    Q_OBJECT
public:
    explicit DropOffPoint(QObject* parent = nullptr);

    /**
     * @brief DropOffPoint Constructor for DropOffPoint class
     * @param row The dropoff point's row in a nxn grid
     * @param col The dropoff point's column in a nxn grid
     * @param product The name of the product for the dropoff point
     */
    DropOffPoint(int row, int col, QString product);

    /**
     * @brief getRow Getter for row of the dropoff point
     * @return The row of the dropoff point
     */
    int getRow();
    /**
     * @brief getCol Getter for col of the dropoff point
     * @return The col of the dropoff point
     */
    int getCol();

    /**
     * @brief getProduct Getter for the product of the dropoff point
     * @return
     */
    QString getProduct();

private:
    int _row;
    int _col;
    QString _product;

signals:

};

#endif // DROPOFFPOINT_H
