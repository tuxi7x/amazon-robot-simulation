#ifndef SHELF_H
#define SHELF_H

#include <QObject>
#include "QVector"
#include "models/Product.h"

/**
 * @brief Model class containing information about a shelf
 */
class Shelf : public QObject
{
    Q_OBJECT
public:
    explicit Shelf(QObject* parent = nullptr);

    /**
     * @brief Shelf Constructor for Shelf class
     * @param row The shelf's row in a nxn grid
     * @param col The docker's column in a nxn grid
     */
    Shelf(int row, int col);

    /**
     * @brief getRow Getter for the current row of the shelf
     * @return The current row of the shelf
     */
    int getRow();

    /**
     * @brief getCol Getter for the current column of the shelf
     * @return The current column of the shelf
     */
    int getCol();

    /**
     * @brief getOriginalRow Getter for the original row of the shelf (useful when it is being moved)
     * @return The original row of the shelf
     */
    int getOriginalRow() const;

    /**
     * @brief getOriginalCol Getter for the original column of the shelf (useful when it is being moved)
     * @return The original column of the shelf
     */
    int getOriginalCol() const;

    /**
     * @brief setRow Setter for the current row of the shelf
     * @param row The new row for the shelf
     */
    void setRow(int row);

    /**
     * @brief setCol Setter for the current column of the shelf
     * @param col The new column for the shelf
     */
    void setCol(int col);

    /**
     * @brief getIsAvailable Checks if the shelf is available
     * @return Returns true if the shelf can be moved
     */
    bool getIsAvailable() const;

    /**
     * @brief setIsAvailable Sets the availability of the shelf
     * @param isAvailable The new availability of the shelf
     */
    void setIsAvailable(bool isAvailable);

private:
    int _row;
    int _col;
    int _originalRow;
    int _originalCol;
    bool _isAvailable;


signals:

};

#endif // SHELF_H
