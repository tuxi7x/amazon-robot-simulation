#include "ViewWrapper.h"

ViewWrapper::ViewWrapper(QObject *parent) : QObject(parent)
{
    _menu = new ApplicationMenu;
    connect (_menu,&ApplicationMenu::editorOpened,this,&ViewWrapper::navigateToEditor);
    _menu->show();
}

void ViewWrapper::navigateToEditor(QRect pos)
{
    delete _menu;
    _editor = new MapEditor;
    connect(_editor,&MapEditor::editorClosed,this,&ViewWrapper::navigateToMenu);
    _editor->setGeometry(pos);
    _editor->show();
}

void ViewWrapper::navigateToMenu(QRect pos)
{
    delete _editor;
    //delete simulationView comes here in the future
    _menu = new ApplicationMenu;
    connect (_menu,&ApplicationMenu::editorOpened,this,&ViewWrapper::navigateToEditor);
    _menu->setGeometry(pos);
    _menu->show();
}

void ViewWrapper::navigateToSimulation(QRect pos)
{
    delete _menu;
    //TODO ...
}
