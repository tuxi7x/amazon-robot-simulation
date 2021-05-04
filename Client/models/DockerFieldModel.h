#ifndef DOCKERFIELDMODEL_H
#define DOCKERFIELDMODEL_H

#include <QObject>
#include <QJsonObject>

/**
 * @brief The DockerFieldModel class Contains the neccesary information about a Docker for the editor and for the simulation.
 */
class DockerFieldModel: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief DockerFieldModel The constructor for this Class.
     * @param row The row of the Docker
     * @param col The column of the Docker
     * @param parent The parent of this Docker as an optional parameter.
     */
    DockerFieldModel(int row, int col, QObject* parent = nullptr);
    /**
     * @brief getRow A getter for the row of this Docker on the grid.
     * @return The row of the Docker
     */
    int getRow() const;
    /**
     * @brief getCol A getter for the column of this Docker on the grid.
     * @return The column of the Docker.
     */
    int getCol() const;
    /**
     * @brief write Writes the information about this Docker to the QJsonObject given as a parameter.
     * @param json The QJsonObject written into.
     */
    void write(QJsonObject &json);
    /**
     * @brief read Reads the information about this Docker from the QJsonObject given as a parameter.
     * @param json The QJsonObject read from.
     */
    void read(const QJsonObject &json);


private:
    int _row;
    int _col;
};

#endif // DOCKERFIELDMODEL_H
