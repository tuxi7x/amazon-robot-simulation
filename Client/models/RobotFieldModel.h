#ifndef ROBOTFIELDMODEL_H
#define ROBOTFIELDMODEL_H

#include <QObject>
#include <QJsonObject>



class RobotFieldModel: public QObject
{
    Q_OBJECT
public:
    RobotFieldModel(int row, int col, int orientation, QObject* parent = nullptr);
    RobotFieldModel(int row, int col, int orientation, int battery, QObject* parent = nullptr);
    int getRow() const;
    int getCol() const;
    int getOrientation() const;

    void write(QJsonObject &json);
    void read(const QJsonObject &json);

    void setOrientation(int orientation);
    int getBattery();

private:
    int _row;
    int _col;
    int _orientation;
    int _battery;
};

#endif // ROBOTFIELDMODEL_H
