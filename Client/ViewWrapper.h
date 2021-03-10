#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QObject>
#include "views/ApplicationMenu.h"
#include "views/MapEditor.h"

class ViewWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ViewWrapper(QObject *parent = nullptr);

signals:

private slots:
    void navigateToEditor(QRect pos);
    void navigateToMenu(QRect pos);
    void navigateToSimulation (QRect pos);

private:
    ApplicationMenu* _menu;
    MapEditor* _editor;

};

#endif // VIEWWRAPPER_H
