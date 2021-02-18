#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include "DialogBase.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QIcon>

class HelpDialog : public DialogBase
{
    Q_OBJECT
public:
    HelpDialog();
    ~HelpDialog();
};

#endif // HELPDIALOG_H
