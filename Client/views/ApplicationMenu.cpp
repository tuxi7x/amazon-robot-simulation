#include "ApplicationMenu.h"

ApplicationMenu::ApplicationMenu(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1024,728);
    setWindowTitle("Királykobrák");
    setStyleSheet("background-color: #118ab2;");

    _mainLayout = new QVBoxLayout();
    _mainLayout->setAlignment(Qt::AlignCenter);
    _mainLayout->setSpacing(60);

    _centralWidget = new QWidget();
    setCentralWidget(_centralWidget);
    _centralWidget->setLayout(_mainLayout);

    _mainTitleLabel = new QLabel("Amazon robotizáció");
    _mainTitleLabel->setStyleSheet("color: white; font-size: 45px; font-weight: bold;");
    _mainTitleLabel->setAlignment(Qt::AlignCenter);

    _editMapButton = new MainMenuButton("Pálya szerkesztése");
    _startSimFromFileButton = new MainMenuButton ("Szimuláció indítása fájlból betöltve");
    _joinRunningSimButton = new MainMenuButton ("Csatlakozás futó szimulációhoz");
    _helpButton = new MainMenuButton("Súgó");

    _mainLayout->addWidget(_mainTitleLabel);
    _mainLayout->addWidget(_editMapButton);
    _mainLayout->addWidget(_startSimFromFileButton);
    _mainLayout->addWidget(_joinRunningSimButton);
    _mainLayout->addWidget(_helpButton);

}

ApplicationMenu::~ApplicationMenu()
{
    delete _mainLayout;
    delete _centralWidget;
    delete _editMapButton;
    delete _startSimFromFileButton;
    delete _joinRunningSimButton;
    delete _helpButton;
}

