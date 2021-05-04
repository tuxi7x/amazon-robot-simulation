#ifndef ROBOTFIELDMODEL_H
#define ROBOTFIELDMODEL_H

#include <QObject>
#include <QJsonObject>


/**
 * @brief The RobotFieldModel class contains the neccesary information about a Robot for the editor and for the simulation.
 */
class RobotFieldModel: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief RobotFieldModel A constructor for this class where battery isnt neccesary.
     * @param row The row of this Robot
     * @param col The column of this robot.
     * @param orientation The orientation of this robot: 0 = north, 1 = east, 2 = south, 3 = west.
     * @param parent The parent of this robot as an optional parameter.
     */
    RobotFieldModel(int row, int col, int orientation, QObject* parent = nullptr);
    /**
     * @brief RobotFieldModel
     * @brief RobotFieldModel A constructor for this class where battery isnt neccesary.
     * @param row The row of this Robot
     * @param col The column of this robot.
     * @param orientation The orientation of this robot: 0 = north, 1 = east, 2 = south, 3 = west.
     * @param battery The current battery level of this robot.
     * @param parent The parent of this robot.
     */
    RobotFieldModel(int row, int col, int orientation, int battery, QObject* parent = nullptr);
    /**
     * @brief getCol A getter for the column of this Robot on the grid.
     * @return The column of the Robot.
     */
    int getCol() const;
    /**
     * @brief write Writes the information about this Robot to the QJsonObject given as a parameter.
     * @param json The QJsonObject written into.
     */
    void write(QJsonObject &json);
    /**
     * @brief read Reads the information about this Robot from the QJsonObject given as a parameter.
     * @param json The QJsonObject read from.
     */
    void read(const QJsonObject &json);
    /**
     * @brief getOrientation A getter for the orientation of this Robot: 0 = north, 1 = east, 2 = south, 3 = west.
     * @return The orientation as an int.
     */
    int getOrientation() const;
    /**
     * @brief setOrientation A setter for the orientation of this Robot: 0 = north, 1 = east, 2 = south, 3 = west.
     * @param orientation The new orientation as an int.
     */
    void setOrientation(int orientation);
    /**
     * @brief getBattery A getter for the current battery level of the Robot.
     * @return The battery level as an int.
     */
    int getBattery();

private:
    int _row;
    int _col;
    int _orientation;
    int _battery;
};

#endif // ROBOTFIELDMODEL_H
