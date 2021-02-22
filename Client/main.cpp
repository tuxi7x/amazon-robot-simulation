#include "views/ApplicationMenu.h"
#include "views/MapEditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationMenu menu;
    MapEditor editor;

    QObject::connect(&menu, SIGNAL(menuClosed(QRect)), &editor, SLOT(openMapEditor(QRect)));
    QObject::connect(&editor, SIGNAL(editorClosed(QRect)), &menu, SLOT(openMainMenu(QRect)));


    menu.show();
    return a.exec();
}
