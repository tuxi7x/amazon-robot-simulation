#include "ConnectDialog.h"

#include <QMovie>


ConnectDialog::ConnectDialog(Connection *connection) : DialogBase()
{
    _connection = connection;
    _timer = new QTimer;
    _timer->setInterval(10000);
    setWindowTitle("Csatlakozás futó szimulációhoz");
    _ipLabel = new QLabel("Szerver IP címe");
    _ipBox = new QLineEdit();

    QRegularExpression ipregex ("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    QRegularExpressionValidator* ipValidator = new QRegularExpressionValidator (ipregex);

    _ipBox->setValidator(ipValidator);

    _portLabel = new QLabel("Port");
    _portBox = new QLineEdit();

    _connectButton = new QPushButton("Csatlakozás");

    _mainLayout = new QVBoxLayout();
    _mainLayout->setSpacing(10);
    _mainLayout->addWidget(_ipLabel);
    _mainLayout->addWidget(_ipBox);
    _mainLayout->addWidget(_portLabel);
    _mainLayout->addWidget(_portBox);
    _mainLayout->addWidget(_connectButton);
    _mainLayout->setAlignment(Qt::AlignCenter);

    _indicator = new QLabel();
    _indicator->setFixedSize(70,70);
    _mainLayout->addWidget(_indicator);
    _mainLayout->setAlignment(_indicator,Qt::AlignHCenter);
    _progressGif = new QMovie(":/Resources/resources/loadingbar.gif");
    _progressGif->setScaledSize(QSize(70,70));

    QString style = this->styleSheet();

    setStyleSheet("color: white; font-size: 20px;" + style);

    _ipBox->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); color: black; border: 1px solid white; border-radius: 10px;}");
    _ipBox->setFixedWidth(_ipBox->width() / 2);
    _ipBox->setFixedHeight(40);
    _portBox->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); color: black; border: 1px solid white; border-radius: 10px;}");
    _portBox->setFixedWidth(_portBox->width() / 2);
    _portBox->setFixedHeight(40);

    _connectButton->setStyleSheet("QPushButton { background-color: #EF476F; border: 1px solid #EF476F; border-radius: 10px; margin-top: 10px;}");
    _connectButton->setFixedWidth(_connectButton->width() / 2);
    _connectButton->setFixedHeight(45);
    _connectButton->setCursor(QCursor(Qt::PointingHandCursor));

    setFixedSize(this->size());
    setLayout(_mainLayout);

    connect(_connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));
    connect(_connection, SIGNAL(connected()),this,SLOT(onConnected()));
    connect(_timer, SIGNAL(timeout()),this,SLOT(connectionTimedOut()));
}

ConnectDialog::~ConnectDialog()
{
    QLayoutItem *child;
    while((child = _mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _mainLayout;
    delete _timer;
}

void ConnectDialog::connectButtonPressed()
{
    if(_ipBox->text() != "" && _portBox->text() != "") {
        _indicator->setMovie(_progressGif);
        _progressGif->start();
        _timer->start();
        _connection->connect(_ipBox->text(), _portBox->text().toInt());
    } else {
        ErrorDialog e ("Először meg kell adni az ip címet és a portot!");
        e.exec();
    }
}

void ConnectDialog::onConnected()
{
    accept();
}

void ConnectDialog::connectionTimedOut()
{
    _progressGif->stop();
    _indicator->setMovie(nullptr);
    ErrorDialog* errorDialog = new ErrorDialog("<b>Hiba:</b><br>A csatlakozás sikertelen (Időtúllépés)!");
    errorDialog->setModal(true);
    errorDialog->exec();
}
