#include "ViewWrapper.h"

ViewWrapper::ViewWrapper(QObject *parent) : QObject(parent)
{
    _connection = new Connection();
    _menu = new ApplicationMenu(_connection);
    _simulation = nullptr;
    _editor = nullptr;
    connect (_menu,&ApplicationMenu::editorOpened,this,&ViewWrapper::navigateToEditor);
    connect (_menu, &ApplicationMenu::connectedToSimulation,this,&ViewWrapper::navigateToSimulation);
    _menu->show();
}

ViewWrapper::~ViewWrapper()
{
    delete _menu;
    delete _simulation;
    delete _editor;
    delete _connection;
}

void ViewWrapper::navigateToEditor(QRect pos)
{
    delete _menu;
    _menu = nullptr;
    _editor = new MapEditor;
    connect(_editor,&MapEditor::editorClosed,this,&ViewWrapper::navigateToMenu);
    _editor->setGeometry(pos);
    _editor->show();
}

void ViewWrapper::navigateToMenu(QRect pos)
{
    if(_editor != nullptr) {delete _editor; _editor = nullptr;}
    if(_simulation != nullptr) {delete _simulation; _simulation = nullptr;}

    _menu = new ApplicationMenu(_connection);
    connect (_menu,&ApplicationMenu::editorOpened,this,&ViewWrapper::navigateToEditor);
    connect (_menu, &ApplicationMenu::connectedToSimulation,this,&ViewWrapper::navigateToSimulation);
    _menu->setGeometry(pos);
    _menu->show();
}

void ViewWrapper::navigateToSimulation(QRect pos)
{
    delete _menu;
    _menu = nullptr;
    _simulation = new SimulationWindow(_connection);
    connect(_simulation,&SimulationWindow::simulationClosed,this,&ViewWrapper::navigateToMenu);
    _simulation->setGeometry(pos);
    _simulation->show();
}
