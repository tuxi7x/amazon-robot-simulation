#include "ConnectDialog.h"


ConnectDialog::ConnectDialog() : DialogBase()
{
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

    _mainLayout->addWidget(_ipLabel);
    _mainLayout->addWidget(_ipBox);
    _mainLayout->addWidget(_portLabel);
    _mainLayout->addWidget(_portBox);

    _mainLayout->addWidget(_connectButton);

    _mainLayout->setAlignment(Qt::AlignCenter);

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
}

void ConnectDialog::connectButtonPressed()
{
    ErrorDialog* errorDialog = new ErrorDialog("<b>Hiba:</b><br>A csatlakozás sikertelen!");
    errorDialog->setModal(true);
    errorDialog->show();
}
