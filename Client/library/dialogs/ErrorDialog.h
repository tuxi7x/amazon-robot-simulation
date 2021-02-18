#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include "library/dialogs/DialogBase.h"
#include <QObject>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>

class ErrorDialog : public DialogBase
{
    Q_OBJECT
public:
    ErrorDialog(QString errorMsg);
    ~ErrorDialog();

private:
    QLabel* _errorLabel;
    QPushButton* _okButton;

protected:
    void paintEvent(QPaintEvent*) override;

};

#endif // ERRORDIALOG_H
