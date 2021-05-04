#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QVBoxLayout>

/**
 * @brief The DialogBase class The base class of the dialogs used in this application.
 */
class DialogBase : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief DialogBase Default constructor.
     */
    DialogBase();

protected:
    QVBoxLayout* _mainLayout;

};

#endif // ABSTRACTDIALOG_H
