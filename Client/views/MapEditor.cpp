#include "MapEditor.h"

MapEditor::MapEditor(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1024,728);
    setWindowTitle("Szerkesztő felület");
    setWindowIcon(QIcon(":/Resources/resources/logo.png"));

    _centralWidget = new QWidget;
    setCentralWidget(_centralWidget);
    _centralWidget->setStyleSheet("background-color: #118ab2;");

}

MapEditor::~MapEditor()
{
    delete _centralWidget;
}

void MapEditor::closeEvent(QCloseEvent *event)
{
    emit editorClosed(this->geometry());
    QMainWindow::closeEvent(event);
}

void MapEditor::openMapEditor(QRect windowPosition)
{
    setGeometry(windowPosition);
    QMainWindow::show();
}



