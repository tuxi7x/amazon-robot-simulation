#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include "DialogBase.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QIcon>

/**
 * @brief The HelpDialog class A special Dialog class used in the main menu to display important informations for the users.
 */
class HelpDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief HelpDialog Default constructor.
     */
    HelpDialog();
    ~HelpDialog();
};

#endif // HELPDIALOG_H
