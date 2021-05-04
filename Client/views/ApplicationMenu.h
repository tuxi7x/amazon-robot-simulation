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

/**
 * @brief The ApplicationMenu class The main menu of this application deriving from QMainWindow it contains the most important dialogs to control the application.
 */
class ApplicationMenu : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief ApplicationMenu The constructor for this Class
     * @param connection The connection of the application as dependency injection.
     * @param parent The parent of this widget.
     */
    ApplicationMenu(Connection* connection, QWidget *parent = nullptr);
    ~ApplicationMenu();


private slots:
    /**
     * @brief openHelpDialog Opens the help dialog when _helpButton is pressed.
     */
    void openHelpDialog();
    /**
     * @brief openConnectDialog Opens ConnectDialog when _joinRunningSimButton is pressed.
     */
    void openConnectDialog();
    /**
     * @brief openStartSimFromFileDialog Opens StartSimFromFileDialog when _startSimFromFileButton is pressed.
     */
    void openStartSimFromFileDialog();
    /**
     * @brief openEditor Initiates the switching to the Editor when _editMapButton is pressed.
     */
    void openEditor();

signals:
    void editorOpened(QRect windowPosition);
    void connectedToSimulation (QRect windowPosition);

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

};
#endif // APPLICATIONMENU_H
