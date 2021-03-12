#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "DialogBase.h"
#include "ErrorDialog.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "controllers/Connection.h"

class ConnectDialog : public DialogBase
{
    Q_OBJECT
public:
    ConnectDialog(Connection* connection);
    ~ConnectDialog();

private slots:
    void connectButtonPressed();

private:
    QLineEdit* _ipBox;
    QLineEdit* _portBox;
    QPushButton* _connectButton;
    QLabel* _ipLabel;
    QLabel* _portLabel;
    QLabel* _indicator;
    QMovie* _progressGif;
    Connection* _connection;

};

#endif // CONNECTDIALOG_H
