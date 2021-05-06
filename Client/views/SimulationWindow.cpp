#include "SimulationWindow.h"

SimulationWindow::SimulationWindow(Connection *connection, QWidget *parent) : QMainWindow(parent)
{
    statusBar()->showMessage("");
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

    _mainLayout->addSpacerItem(new QSpacerItem(90,728));
    _mainLayout->addLayout(_gridContainer);
    _mainLayout->addLayout(_sidePanel);
    _mainLayout->setAlignment(_gridContainer,Qt::AlignLeft);
    _mainLayout->setAlignment(_gridContainer,Qt::AlignVCenter);
    _sidePanel->setSpacing(35);
    _mainLayout->setSpacing(25);
    _mainLayout->setAlignment(_sidePanel,Qt::AlignCenter);

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

    connect(_disconnectButton,&QPushButton::clicked, this, &SimulationWindow::onDisconnectButtonClicked);
    connect(_finishSimButton, &QPushButton::clicked, this, &SimulationWindow::onFinishButtonClicked);

    connect(_connection,&Connection::createMap, this, &SimulationWindow::onCreateMapSignal);
    connect(_connection,&Connection::fieldToRobot, this, &SimulationWindow::onFieldToRobotSignal);
    connect(_connection,&Connection::fieldToEmpty, this, &SimulationWindow::onFieldToEmptySignal);
    connect(_connection,&Connection::fieldToShelf, this,  &SimulationWindow::onFieldToShelfSignal);
    connect(_connection,&Connection::fieldToDropOff, this,  &SimulationWindow::onFieldToDropOffSignal);
    connect(_connection,&Connection::fieldToDocker, this, &SimulationWindow::onFieldtoDockerSignal);
    connect(_connection, &Connection::gameSpeedChanged, this, &SimulationWindow::onGameSpeedChangedSignal);
    connect(_connection, &Connection::pauseStateChanged, this, &SimulationWindow::onPauseStateChangedSignal);
    connect(_pauseResumeButton, SIGNAL(clicked()), this, SLOT(onPauseResumeButtonClicked()));
    connect(_newOrderButton, SIGNAL(clicked()), this, SLOT(onNewOrderButtonClicked()));
    connect(_speedSlider, &QSlider::actionTriggered, this, &SimulationWindow::onSpeedSliderValueChanged);
    connect(_connection, &Connection::productDelivered, this, [&](QString product){this->statusBar()->showMessage(QString("%1 kiszállítva").arg(product));});

    _paused = false;
    onCreateMapSignal(6); //An initial map to when still loading

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
    while(!_mapGrid->isEmpty()) {
        QLayoutItem* l = _mapGrid->takeAt(0);
        delete l->widget();
        delete l;
    }
    _buttons.clear();
    for(int i=0; i<size;i++) {
        QVector<SimulationButton*> v;
        for(int j=0;j<size;j++) {
            SimulationButton* btn = new SimulationButton(i, j);
            btn->setFixedSize(QSize(630/6,630/6));
            btn->setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
            btn->setText("");
            btn->setFixedSize(QSize(630/size,630/size));
            connect(btn, &SimulationButton::clicked, this, &SimulationWindow::onFieldButtonPressed);
            _mapGrid->addWidget(btn,i,j);
            v.append(btn);
        }
        _buttons.append(v);
    }
}

void SimulationWindow::onFieldToRobotSignal(int row, int col, int orientation, int battery)
{
    //TODO orientation
    if(orientation == 0)  {
        _buttons[row][col]->setStyleSheet("border-image:url(:/Resources/resources/robot_up.png); background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    } else if(orientation == 1) {
         _buttons[row][col]->setStyleSheet("border-image:url(:/Resources/resources/robot_right.png); background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    } else if(orientation == 2) {
         _buttons[row][col]->setStyleSheet("border-image:url(:/Resources/resources/robot_down.png); background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    } else if (orientation == 3) {
         _buttons[row][col]->setStyleSheet("border-image:url(:/Resources/resources/robot_left.png); background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    }

}

void SimulationWindow::onFieldToEmptySignal(int row, int col)
{
    _buttons[row][col]->setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
}

void SimulationWindow::onFieldToShelfSignal(int row, int col)
{
    bool robotOnIt = _connection->robotOnField(row,col);
    bool atDropOff = _connection->dropOffInPosition(row,col);
    _buttons[row][col]->setStyleSheet("background-color: #06d6a0; color:white; font-size: 30px; border: 1px solid black;");
    if(robotOnIt && atDropOff) _buttons[row][col]->setStyleSheet(_buttons[row][col]->styleSheet() + "border-image:url(:/Resources/resources/robotpolccelallomas.png);");
    else if(robotOnIt) _buttons[row][col]->setStyleSheet(_buttons[row][col]->styleSheet() + "border-image:url(:/Resources/resources/robotpolc.png);");
    _buttons[row][col]->setText("P");
}

void SimulationWindow::onFieldToDropOffSignal(int row, int col, QString product)
{
    int fontSize = 30;
    if(product.length() > 5 || _connection->getSize() > 7) fontSize-= 10;
    if(_connection->getSize()>9) fontSize-=5;
    QString font = QString::number(fontSize);


    _buttons[row][col]->setStyleSheet(QString("background-color: #907f9f; color:white; font-size: %1px; border: 1px solid black;").arg(font));
    _buttons[row][col]->setText(QString("C\n(%1)").arg(product));
}

void SimulationWindow::onFieldtoDockerSignal(int row, int col)
{
    bool robotOnIt = _connection->robotOnField(row,col);
    _buttons[row][col]->setStyleSheet("background-color: #f26419; color:white; font-size: 30px; border: 1px solid black;");
    if(robotOnIt) _buttons[row][col]->setStyleSheet(_buttons[row][col]->styleSheet() + "border-image:url(:/Resources/resources/robotpolc.png);");
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
void SimulationWindow::onPauseResumeButtonClicked()
{
    if(_paused) {
        _connection->resumeState();
        _paused = false;
    } else {
        _connection->pauseState();
        _paused = true;
    }
}


void SimulationWindow::onFieldButtonPressed()
{
    SimulationButton* s = qobject_cast<SimulationButton*> (sender());
    QPair<Connection::FieldTypes, QObject*> res = _connection->getField(s->getRow(), s->getCol());
    if(res.first == Connection::Shelf) {
            QVector<QString> productsOnThisShelf = _connection->getProductsOnShelf(s->getRow(), s->getCol());
            ProductsOnShelfDialog posd (productsOnThisShelf);
            posd.exec();
    }else if (res.first == Connection::Robot) {
    RobotFieldModel* selectedRobot = qobject_cast<RobotFieldModel*> (res.second);
    RobotInfoDialog robotdialog (selectedRobot->getBattery());
    robotdialog.exec();
    }
}

void SimulationWindow::onFinishButtonClicked()
{
    _connection->finishSimulation();
    emit simulationClosed(this->geometry());
}

void SimulationWindow::onDisconnectButtonClicked()
{
    _connection->disconnectSimulation();
    emit simulationClosed(this->geometry());
}

void SimulationWindow::onNewOrderButtonClicked()
{
    QVector<ProductModel*> products = _connection->getProducts();
    QVector<QString> orders = _connection->getOrders();
    QVector<QString> newOrders;

    NewOrderDialog nod(products, orders);
    if(nod.exec()) {
        for(int i = 0; i<nod.getOrders().length(); i++) {
            newOrders.append(nod.getOrders()[i]);
        }
        _connection->addNewOrders(newOrders);
        _connection->newOrder();
    }

}

void SimulationWindow::onSpeedSliderValueChanged()
{
    _connection->speedChanged(_speedSlider->sliderPosition());
}


