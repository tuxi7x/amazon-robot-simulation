#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(Connection *connection, QWidget *parent) : QMainWindow(parent)
{
    _connection = connection;
    setFixedSize(1024,728);
    setWindowTitle("Szimuláció");
    setWindowIcon(QIcon(":/Resources/resources/logo.png"));
    _centralWidget = new QWidget();
    setCentralWidget(_centralWidget);
    _centralWidget->setStyleSheet("background-color: #118ab2;");

    _mainLayout = new QHBoxLayout(_centralWidget);
    _mapGrid = new QGridLayout;
    _mapGrid->setSpacing(0);
    _sidePanel = new QVBoxLayout;
    _gridContainer = new QVBoxLayout;
    _gridContainer->addLayout(_mapGrid);

    _mainLayout->addLayout(_gridContainer);
    _mainLayout->addLayout(_sidePanel);
    _mainLayout->setAlignment(_gridContainer,Qt::AlignCenter);
    _sidePanel->setSpacing(35);
    _mainLayout->setSpacing(25);
    _sidePanel->setAlignment(Qt::AlignVCenter);

    _newOrderButton = new QPushButton("Új rendelés");
    _pauseResumeButton = new QPushButton("Megállítás");
    _finishSimButton = new QPushButton ("Befejezés");
    _disconnectButton = new QPushButton("Lecsatlakozás");

    _newOrderButton->setFixedSize(140,40);
    _pauseResumeButton->setFixedSize(140,40);
    _finishSimButton->setFixedSize(140,40);
    _disconnectButton->setFixedSize(140,40);
    _newOrderButton->setStyleSheet("background-color: #06D6A0; color: white; border: none; font-size:21px;");
    _pauseResumeButton->setStyleSheet("background-color: #F26419; color: white; border: none; font-size:21px;");
    _finishSimButton->setStyleSheet("background-color: #34B1FF; color: white; border: none; font-size:21px;");
    _disconnectButton->setStyleSheet("background-color: #EF476F; color: white; border: none; font-size:21px;");

    _sidePanel->addWidget(_newOrderButton);
    _sidePanel->addWidget(_pauseResumeButton);
    _sidePanel->addWidget(_finishSimButton);
    _sidePanel->addWidget(_disconnectButton);

    createMap();

}

void SimulationWindow::createMap()
{
    for(int i=0; i<6;i++) {
        for(int j=0;j<6;j++) {
            QPushButton* btn = new QPushButton();
            btn->setFixedSize(QSize(630/6,630/6));
            btn->setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
            btn->setText("");
            _mapGrid->addWidget(btn,i,j);
        }
    }
}
