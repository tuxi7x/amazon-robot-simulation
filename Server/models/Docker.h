#ifndef DOCKER_H
#define DOCKER_H

#include <QObject>
#include "models/Robot.h"

class Docker : public QObject
{
    Q_OBJECT
public:
    explicit Docker(QObject *parent = nullptr);
private:
    int _id;
    int _index;
    Robot _robot;
    int _timer;

signals:

};

#endif // DOCKER_H
