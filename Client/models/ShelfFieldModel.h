#ifndef SHELFFIELDMODEL_H
#define SHELFFIELDMODEL_H

#include <QObject>
#include <QJsonObject>

/**
 * @brief The ShelfFieldModel class contains the neccesary information about a shelf for the editor and for the simulation.
 */
class ShelfFieldModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ShelfFieldModel
     * @param row The row of the Docker
     * @param col The column of the Docker
     * @param parent The parent of this Docker as an optional parameter.
     */
    ShelfFieldModel(int row, int col, QObject* parent = nullptr);
    /**
     * @brief getRow A getter for the row of this Docker on the grid.
     * @return The row of the Docker
     */
    int getRow() const;
    /**
     * @brief getCol A getter for the column of this Shelf on the grid.
     * @return The column of the Shelf.
     */
    int getCol() const;
    /**
     * @brief write Writes the information about this Shelf to the QJsonObject given as a parameter.
     * @param json The QJsonObject written into.
     */
    void write(QJsonObject &json);
    /**
     * @brief read Reads the information about this Shelf from the QJsonObject given as a parameter.
     * @param json The QJsonObject read from.
     */
    void read(const QJsonObject &json);
    /**
     * @brief setRow A setter for the current row of this shelf.
     * @param row The new row of this shelf.
     */
    void setRow(int row);
    /**
     * @brief setCol A setter for the current column of this shelf.
     * @param col The new column of this shelf.
     */
    void setCol(int col);

private:
    int _row;
    int _col;
};

#endif // SHELFFIELDMODEL_H
