#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "DialogBase.h"
#include "ErrorDialog.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include "controllers/Connection.h"

/**
 * @brief The ConnectDialog class Is a specific Dialog that is used in the Main menu to connect to a server where a simulation is already running.
 */
class ConnectDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief ConnectDialog The constructor for this class.
     * @param connection The connection object of this application with dependency injection.
     */
    ConnectDialog(Connection* connection);
    ~ConnectDialog();

private slots:
    void connectButtonPressed();
    void onConnected();
    void connectionTimedOut();

private:
    QLineEdit* _ipBox;
    QLineEdit* _portBox;
    QPushButton* _connectButton;
    QLabel* _ipLabel;
    QLabel* _portLabel;
    QLabel* _indicator;
    QMovie* _progressGif;
    Connection* _connection;
    QTimer* _timer;

};

#endif // CONNECTDIALOG_H
