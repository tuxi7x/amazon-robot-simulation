#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QVBoxLayout>

class DialogBase : public QDialog
{
    Q_OBJECT
public:
    DialogBase();

protected:
    QVBoxLayout* _mainLayout;

};

#endif // ABSTRACTDIALOG_H
