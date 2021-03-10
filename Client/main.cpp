#include "views/ApplicationMenu.h"
#include "views/MapEditor.h"
#include "ViewWrapper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewWrapper vw;


    return a.exec();
}
