#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "DialogBase.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ConnectDialog : public DialogBase
{
    Q_OBJECT
public:
    ConnectDialog();
};

#endif // CONNECTDIALOG_H
