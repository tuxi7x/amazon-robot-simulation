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
#include "controllers/Connection.h"

class StartSimFromFileDialog : public DialogBase
{
    Q_OBJECT
public:
    StartSimFromFileDialog(Connection* connection);
    ~StartSimFromFileDialog();

private slots:
    void connectButtonPressed();
    void browseButtonPressed();

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
    Connection* _connection;

    QFile* _file;

};

#endif // STARTSIMFROMFILEDIALOG_H
