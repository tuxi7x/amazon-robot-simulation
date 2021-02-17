#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "library/buttons/MainMenuButton.h"

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

public:
    ApplicationMenu(QWidget *parent = nullptr);
    ~ApplicationMenu();
};
#endif // APPLICATIONMENU_H
