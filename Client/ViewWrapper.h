#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include <QObject>
#include "views/ApplicationMenu.h"
#include "views/MapEditor.h"
#include "views/SimulationWindow.h"
#include "controllers/Connection.h"

/**
 * @brief The ViewWrapper class Is a special class used to handle the transitions between the views of this application.
 */
class ViewWrapper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ViewWrapper Default constructor with an optional parent parameter.
     * @param parent The parent of this QObject
     */
    explicit ViewWrapper(QObject *parent = nullptr);
    ~ViewWrapper();

private slots:
    /**
     * @brief navigateToEditor Navigates to the Editor view.
     * @param pos The position of the application on the screen.
     */
    void navigateToEditor(QRect pos);
    /**
     * @brief navigateToMenu Navigates to the Main menu view.
     * @param pos The position of the application on the screen.
     */
    void navigateToMenu(QRect pos);
    /**
     * @brief navigateToSimulation Navigates to the Simulation window view.
     * @param pos The position of the application on the screen.
     */
    void navigateToSimulation (QRect pos);

private:
    ApplicationMenu* _menu;
    MapEditor* _editor;
    SimulationWindow* _simulation;
    Connection* _connection;


};

#endif // VIEWWRAPPER_H
