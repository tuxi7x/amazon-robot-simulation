#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QObject>
#include "views/ApplicationMenu.h"
#include "views/MapEditor.h"
#include "views/SimulationWindow.h"
#include "controllers/Connection.h"

class ViewWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ViewWrapper(QObject *parent = nullptr);
    ~ViewWrapper();

signals:

private slots:
    void navigateToEditor(QRect pos);
    void navigateToMenu(QRect pos);
    void navigateToSimulation (QRect pos);

private:
    ApplicationMenu* _menu;
    MapEditor* _editor;
    SimulationWindow* _simulation;
    Connection* _connection;


};

#endif // VIEWWRAPPER_H
