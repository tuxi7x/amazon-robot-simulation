#ifndef ROBOTFIELDMODEL_H
#define ROBOTFIELDMODEL_H


class RobotFieldModel
{
public:
    RobotFieldModel(int row, int col, int orientation);

    int getRow() const;
    int getCol() const;
    int getOrientation() const;

private:
    int _row;
    int _col;
    int _orientation;
};

#endif // ROBOTFIELDMODEL_H
