#ifndef ROBOTINFODIALOG_H
#define ROBOTINFODIALOG_H

#include "library/dialogs/DialogBase.h"
#include "QListWidget"

/**
 * @brief The RobotInfoDialog class A special dialog showing the user the information about a robot during simulation.
 */
class RobotInfoDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief RobotInfoDialog A constructor for this class.
     * @param battery The current battery of the robot.
     */
    RobotInfoDialog(int battery);
private:
    QListWidget* _list;
};

#endif // ROBOTINFODIALOG_H
