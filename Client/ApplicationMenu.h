#ifndef APPLICATIONMENU_H
#define APPLICATIONMENU_H

#include <QMainWindow>

class ApplicationMenu : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationMenu(QWidget *parent = nullptr);
    ~ApplicationMenu();
};
#endif // APPLICATIONMENU_H
