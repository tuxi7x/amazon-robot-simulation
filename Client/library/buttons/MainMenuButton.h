#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QString>

class MainMenuButton : public QPushButton
{
public:
    MainMenuButton(const QString &text, QWidget *parent = nullptr);

};

#endif // MAINMENUBUTTON_H
