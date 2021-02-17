#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "library/buttons/MainMenuButton.h"
#include "library/dialogs/HelpDialog.h"
#include "library/dialogs/ConnectDialog.h"
#include <QGraphicsOpacityEffect>
#include <QIcon>

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

public:
    ApplicationMenu(QWidget *parent = nullptr);
    ~ApplicationMenu();

private slots:
    void openHelpDialog();
    void openConnectDialog();
    void closeDialog();
};
#endif // APPLICATIONMENU_H
