#ifndef ROBOTINFODIALOG_H
#define ROBOTINFODIALOG_H

#include "library/dialogs/DialogBase.h"
#include "QListWidget"

class RobotInfoDialog : public DialogBase
{
    Q_OBJECT
public:
    RobotInfoDialog(int battery);
private:
    QListWidget* _list;
};

#endif // ROBOTINFODIALOG_H
