#ifndef DOCKER_H
#define DOCKER_H

#include <QObject>
#include "models/Robot.h"

/**
 * @brief Model class containg information about a docker
 */
class Docker : public QObject
{
    Q_OBJECT
public:

    explicit Docker(QObject* parent = nullptr);

    /**
     * @brief Docker Constructor for Docker class
     * @param row The docker's row in a nxn grid
     * @param col The docker's column in a nxn grid
     */
    Docker(int row, int col);

    /**
     * @brief getRow Getter for row of Docker
     * @return The row of the Docker
     */
    int getRow();

    /**
     * @brief getCol Getter for the column of Docker
     * @return The column of the Docker
     */
    int getCol();
    bool getIsOccupied() const;
    void setIsOccupied(bool value);

private:
    int _row;
    int _col;
    Robot _robot;
    int _timer;
    bool isOccupied;

signals:

};

#endif // DOCKER_H
