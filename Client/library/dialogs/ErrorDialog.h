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

/**
 * @brief The ErrorDialog class Is a special dialog commonly used in the application to display error messages.
 */
class ErrorDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief ErrorDialog A constructor for this class
     * @param errorMsg The message displayed on the error dialog.
     */
    ErrorDialog(QString errorMsg);
    ~ErrorDialog();

private:
    QLabel* _errorLabel;
    QPushButton* _okButton;

protected:
    /**
     * @brief paintEvent The paint event redefined in order to make the dialog round.
     */
    void paintEvent(QPaintEvent*) override;

};

#endif // ERRORDIALOG_H
