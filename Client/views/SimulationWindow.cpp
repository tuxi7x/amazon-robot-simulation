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

    _speedLabel = new QLabel("Sebesség: 1"); //Just for testing the UI
    _speedSlider = new QSlider(Qt::Horizontal);
    _newOrderButton = new QPushButton("Új rendelés");
    _pauseResumeButton = new QPushButton("Megállítás"); //Just for testing the UI
    _finishSimButton = new QPushButton ("Befejezés");
    _disconnectButton = new QPushButton("Lecsatlakozás");

    _speedLabel->setStyleSheet("color:white; font-size:20px; text-align: center;");
    _speedSlider->setFixedSize(140,40);
    _speedSlider->setRange(1,3);
    _speedSlider->setStyleSheet("QSlider::handle:horizontal { "
                      "background-color:gray;"
                      "} ");
    _newOrderButton->setFixedSize(140,40);
    _pauseResumeButton->setFixedSize(140,40);
    _finishSimButton->setFixedSize(140,40);
    _disconnectButton->setFixedSize(140,40);
    _newOrderButton->setStyleSheet("background-color: #06D6A0; color: white; border: none; font-size:21px;");
    _pauseResumeButton->setStyleSheet("background-color: #F26419; color: white; border: none; font-size:21px;");
    _finishSimButton->setStyleSheet("background-color: #34B1FF; color: white; border: none; font-size:21px;");
    _disconnectButton->setStyleSheet("background-color: #EF476F; color: white; border: none; font-size:21px;");

    _sidePanel->addWidget(_speedLabel);
    _sidePanel->setAlignment(_speedLabel,Qt::AlignHCenter);
    _sidePanel->addWidget(_speedSlider);
    _sidePanel->addWidget(_newOrderButton);
    _sidePanel->addWidget(_pauseResumeButton);
    _sidePanel->addWidget(_finishSimButton);
    _sidePanel->addWidget(_disconnectButton);

    connect(_disconnectButton,&QPushButton::clicked, this, [&](){emit simulationClosed(this->geometry());});
    connect(_finishSimButton, &QPushButton::clicked, this, [&](){emit simulationClosed(this->geometry());});

    connect(_connection,&Connection::createMap, this, &SimulationWindow::onCreateMapSignal);
    connect(_connection,&Connection::fieldToRobot, this, &SimulationWindow::onFieldToRobotSignal);
    connect(_connection,&Connection::fieldToEmpty, this, &SimulationWindow::onFieldToEmptySignal);
    connect(_connection,&Connection::fieldToShelf, this,  &SimulationWindow::onFieldToShelfSignal);
    connect(_connection,&Connection::fieldToDropOff, this,  &SimulationWindow::onFieldToDropOffSignal);
    connect(_connection, &Connection::gameSpeedChanged, this, &SimulationWindow::onGameSpeedChangedSignal);
    connect(_connection, &Connection::pauseStateChanged, this, &SimulationWindow::onPauseStateChangedSignal);


    void createMap (int size);
    //Orientations: 0 = up, 1 = right, 2 = down, 3 = left
    void fieldToRobot (int row, int col, int orientation, int battery);
    void fieldToEmpty (int row, int col);
    void fieldToShelf (int row, int col);
    void fieldToDropOffEvent (int row, int col);
    void gameSpeedChanged (int newSpeed);
    void pauseStateChanged (bool paused);


    onCreateMapSignal(6); //Just for testing the UI

}

SimulationWindow::~SimulationWindow()
{
    QLayoutItem* child;
    while((child = _mapGrid->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    while((child = _sidePanel->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    while((child = _gridContainer->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    while((child = _mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _mainLayout;
    delete _centralWidget;
}


void SimulationWindow::onCreateMapSignal(int size)
{

    for(int i=0; i<size;i++) {
        QVector<QPushButton*> v;
        for(int j=0;j<size;j++) {
            QPushButton* btn = new QPushButton();
            btn->setFixedSize(QSize(630/6,630/6));
            btn->setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
            btn->setText("");
            _mapGrid->addWidget(btn,i,j);
            v.append(btn);
        }
        _buttons.append(v);
    }
}

void SimulationWindow::onFieldToRobotSignal(int row, int col, int orientation, int battery)
{
    //TODO orientation
    _buttons[row][col]->setStyleSheet("background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    _buttons[row][col]->setText("R");
}

void SimulationWindow::onFieldToEmptySignal(int row, int col)
{
    _buttons[row][col]->setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
}

void SimulationWindow::onFieldToShelfSignal(int row, int col)
{
    _buttons[row][col]->setStyleSheet("background-color: #06d6a0; color:white; font-size: 30px; border: 1px solid black;");
    _buttons[row][col]->setText("P");
}

void SimulationWindow::onFieldToDropOffSignal(int row, int col)
{
    _buttons[row][col]->setStyleSheet("background-color: #907f9f; color:white; font-size: 30px; border: 1px solid black;");
    _buttons[row][col]->setText("C");
}

void SimulationWindow::onFieldtoDockerSignal(int row, int col)
{
    _buttons[row][col]->setStyleSheet("background-color: #f26419; color:white; font-size: 30px; border: 1px solid black;");
    _buttons[row][col]->setText("D");
}



void SimulationWindow::onGameSpeedChangedSignal(int newSpeed)
{
    _speedLabel->setText("Sebesség: " + QString::number(newSpeed));
    _speedSlider->setValue(newSpeed);
}

void SimulationWindow::onPauseStateChangedSignal(bool paused)
{
    paused ? _pauseResumeButton->setText("Folytatás") : _pauseResumeButton->setText("Megállítás");
}
