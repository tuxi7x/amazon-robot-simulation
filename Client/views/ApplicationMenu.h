#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "library/buttons/MainMenuButton.h"
#include "library/dialogs/HelpDialog.h"
#include "library/dialogs/ConnectDialog.h"
#include "library/dialogs/StartSimFromFileDialog.h"
#include <QCloseEvent>
#include <QGraphicsOpacityEffect>
#include <QIcon>
#include "controllers/Connection.h"

class ApplicationMenu : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout* _mainLayout;
    QWidget* _centralWidget;
    QLabel* _mainTitleLabel;
    MainMenuButton* _helpButton;
    MainMenuButton* _editMapButton;
    MainMenuButton* _startSimFromFileButton;
    MainMenuButton* _joinRunningSimButton;
    QGraphicsOpacityEffect* _opacityEffect;
    HelpDialog* _helpDialog;
    ConnectDialog* _connectDialog;
    StartSimFromFileDialog* _startSimFromFileDialog;


public:
    ApplicationMenu(Connection* connection, QWidget *parent = nullptr);
    ~ApplicationMenu();


private slots:
    void openHelpDialog();
    void openConnectDialog();
    void openStartSimFromFileDialog();
    void openEditor();

signals:
    void editorOpened(QRect windowPosition);
    void connectedToSimulation (QRect windowPosition);

};
#endif // APPLICATIONMENU_H
