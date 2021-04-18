#ifndef DOCKER_H
#define DOCKER_H

#include <QObject>
#include "models/Robot.h"

class Docker : public QObject
{
    Q_OBJECT
public:
    explicit Docker(QObject *parent = nullptr);
    Docker(int row, int col);
    int getRow();
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
