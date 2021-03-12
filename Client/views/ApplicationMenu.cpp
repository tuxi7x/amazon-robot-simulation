#include "ApplicationMenu.h"



ApplicationMenu::ApplicationMenu(Connection *connection, QWidget *parent)
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

    _connectDialog = new ConnectDialog(connection);

    _startSimFromFileDialog = new StartSimFromFileDialog(connection);

    _mainLayout->addWidget(_mainTitleLabel);
    _mainLayout->addWidget(_editMapButton);
    _mainLayout->addWidget(_startSimFromFileButton);
    _mainLayout->addWidget(_joinRunningSimButton);
    _mainLayout->addWidget(_helpButton);

    connect(_helpButton,SIGNAL(clicked()),this,SLOT(openHelpDialog()));
    connect(_joinRunningSimButton, SIGNAL(clicked()),this,SLOT(openConnectDialog()));
    connect(_startSimFromFileButton, SIGNAL(clicked()), this, SLOT(openStartSimFromFileDialog()));
    connect(_editMapButton,SIGNAL(clicked()),this,SLOT(openEditor()));

}

ApplicationMenu::~ApplicationMenu()
{
    QLayoutItem* child;
    while((child = _mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _helpDialog;
    delete _opacityEffect;
    delete _connectDialog;
    delete _startSimFromFileDialog;
    delete _mainLayout;
    delete _centralWidget;
}

void ApplicationMenu::openHelpDialog() {
    _opacityEffect->setEnabled(true);
    _helpDialog->exec();
    _opacityEffect->setEnabled(false);
}

void ApplicationMenu::openConnectDialog() {
    _opacityEffect->setEnabled(true);
    if(_connectDialog->exec() == QDialog::Accepted) {
        emit connectedToSimulation(this->geometry()); //Pass connection as a parameter when its implemented!
    }
    else _opacityEffect->setEnabled(false);
}

void ApplicationMenu::openStartSimFromFileDialog()
{
    _opacityEffect->setEnabled(true);
    if(_startSimFromFileDialog->exec() == QDialog::Accepted) {

    }
    else _opacityEffect->setEnabled(false);
}


void ApplicationMenu::openEditor()
{
    emit editorOpened(this->geometry());
}




