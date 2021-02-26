#ifndef ROBOTFIELDMODEL_H
#define ROBOTFIELDMODEL_H

#include <QObject>



class RobotFieldModel: public QObject
{
    Q_OBJECT
public:
    RobotFieldModel(int row, int col, int orientation, QObject* parent = nullptr);
    int getRow() const;
    int getCol() const;
    int getOrientation() const;

private:
    int _row;
    int _col;
    int _orientation;
};

#endif // ROBOTFIELDMODEL_H
