#include "ApplicationMenu.h"


ApplicationMenu::ApplicationMenu(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1024,728);
    setWindowTitle("Királykobrák");
    setWindowIcon(QIcon(":/Resources/resources/logo.png"));


    _mainLayout = new QVBoxLayout();
    _mainLayout->setAlignment(Qt::AlignCenter);
    _mainLayout->setSpacing(60);

    _centralWidget = new QWidget();
    setCentralWidget(_centralWidget);
    _centralWidget->setLayout(_mainLayout);
    _centralWidget->setStyleSheet("background-color: #118ab2;");

    _mainTitleLabel = new QLabel("Amazon robotizáció");
    _mainTitleLabel->setStyleSheet("color: white; font-size: 45px; font-weight: bold;");
    _mainTitleLabel->setAlignment(Qt::AlignCenter);

    _editMapButton = new MainMenuButton("Pálya szerkesztése");
    _startSimFromFileButton = new MainMenuButton ("Szimuláció indítása fájlból betöltve");
    _joinRunningSimButton = new MainMenuButton ("Csatlakozás futó szimulációhoz");
    _helpButton = new MainMenuButton("Súgó");

    _opacityEffect = new QGraphicsOpacityEffect();
    _opacityEffect->setOpacity(0.7);
    _centralWidget->setGraphicsEffect(_opacityEffect);
    _opacityEffect->setEnabled(false);

    _helpDialog = new HelpDialog();
    _helpDialog->setModal(true);
    connect(_helpDialog,SIGNAL(rejected()),this,SLOT(closeDialog()));

    _connectDialog = new ConnectDialog();
    _connectDialog->setModal(true);
    connect(_connectDialog,SIGNAL(rejected()),this,SLOT(closeDialog()));

    _startSimFromFileDialog = new StartSimFromFileDialog();
    _startSimFromFileDialog->setModal(true);
    connect(_startSimFromFileDialog,SIGNAL(rejected()),this,SLOT(closeDialog()));

    _mainLayout->addWidget(_mainTitleLabel);
    _mainLayout->addWidget(_editMapButton);
    _mainLayout->addWidget(_startSimFromFileButton);
    _mainLayout->addWidget(_joinRunningSimButton);
    _mainLayout->addWidget(_helpButton);

    connect(_helpButton,SIGNAL(clicked()),this,SLOT(openHelpDialog()));
    connect(_joinRunningSimButton, SIGNAL(clicked()),this,SLOT(openConnectDialog()));
    connect(_startSimFromFileButton, SIGNAL(clicked()), this, SLOT(openStartSimFromFileDialog()));

}

ApplicationMenu::~ApplicationMenu()
{
    for (int i = 0;i < _mainLayout->count() ; i++ ) {
        delete _mainLayout->itemAt(i);
    }
    delete _mainLayout;
    delete _centralWidget;
}

void ApplicationMenu::openHelpDialog() {
    _opacityEffect->setEnabled(true);
    _helpDialog->show();
}

void ApplicationMenu::openConnectDialog() {
    _opacityEffect->setEnabled(true);
    _connectDialog->show();
}

void ApplicationMenu::openStartSimFromFileDialog()
{
    _opacityEffect->setEnabled(true);
    _startSimFromFileDialog->show();
}

void ApplicationMenu::closeDialog() {
    _opacityEffect->setEnabled(false);
}

