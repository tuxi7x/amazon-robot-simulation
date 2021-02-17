#include "ApplicationMenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationMenu w;
    w.show();
    return a.exec();
}
