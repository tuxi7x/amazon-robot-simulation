#ifndef STARTSIMFROMFILEDIALOG_H
#define STARTSIMFROMFILEDIALOG_H

#include "DialogBase.h"
#include <QObject>
#include "ErrorDialog.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QMovie>
#include <QTimer>
#include "controllers/Connection.h"

/**
 * @brief The StartSimFromFileDialog class A dialog class used by the main menu to allow the user to start a new simulation on a specific
 * server with a map given by the user.
 */
class StartSimFromFileDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief StartSimFromFileDialog
     * @param connection The connection object of this application with dependency injection.
     */
    StartSimFromFileDialog(Connection* connection);
    ~StartSimFromFileDialog();

private slots:
    void connectButtonPressed();
    void browseButtonPressed();
    void onConnected();
    void connectionTimedOut();

private:
    QLineEdit* _ipBox;
    QLineEdit* _portBox;
    QPushButton* _connectButton;
    QLabel* _ipLabel;
    QLabel* _portLabel;
    QHBoxLayout* _browseFileLine;
    QPushButton* _browseFileButton;
    QLabel* _selectedFileLabel;
    QLabel* _browseFileLabel;
    QLabel* _indicator;
    QMovie* _progressGif;
    Connection* _connection;
    QTimer* _timer;

    QFile* _file;

};

#endif // STARTSIMFROMFILEDIALOG_H
