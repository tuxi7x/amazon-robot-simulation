#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "DialogBase.h"
#include "ErrorDialog.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>

class ConnectDialog : public DialogBase
{
    Q_OBJECT
public:
    ConnectDialog(QTcpSocket* connection);
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
    QTcpSocket* _connection;

};

#endif // CONNECTDIALOG_H
