#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QString>

/**
 * @brief The MainMenuButton class is a special QPushButton that is used in the main menu of the application.
 * It is a circular shaped fat yellow button.
 */
class MainMenuButton : public QPushButton
{
public:
    /**
     * @brief MainMenuButton
     * @param text The text that will be displayed on the Button
     * @param parent The parent of this Button
     */
    MainMenuButton(const QString &text, QWidget *parent = nullptr);

};

#endif // MAINMENUBUTTON_H
