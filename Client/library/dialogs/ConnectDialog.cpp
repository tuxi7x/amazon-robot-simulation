#include "ConnectDialog.h"

ConnectDialog::ConnectDialog() : DialogBase()
{
    setWindowTitle("Csatlakozás futó szimulációhoz");

    QLabel* ipLabel = new QLabel("Szerver IP címe");
    QLineEdit* ipBox = new QLineEdit();

    QLabel* portLabel = new QLabel("Port");
    QLineEdit* portBox = new QLineEdit();

    QPushButton* connect = new QPushButton("Csatlakozás");

    _mainLayout = new QVBoxLayout();

    _mainLayout->addWidget(ipLabel);
    _mainLayout->addWidget(ipBox);

    _mainLayout->addWidget(portLabel);
    _mainLayout->addWidget(portBox);

    _mainLayout->addWidget(connect);

    _mainLayout->setAlignment(Qt::AlignCenter);

    QString style = this->styleSheet();

    setStyleSheet("color: white; font-size: 20px;" + style);

    ipBox->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); color: black; border: 1px solid white; border-radius: 10px;}");
    ipBox->setFixedWidth(ipBox->width() / 2);
    ipBox->setFixedHeight(40);
    portBox->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(233, 99, 0); color: black; border: 1px solid white; border-radius: 10px;}");
    portBox->setFixedWidth(portBox->width() / 2);
    portBox->setFixedHeight(40);

    connect->setStyleSheet("QPushButton { background-color: #EF476F; border: 1px solid #EF476F; border-radius: 10px; margin-top: 10px;}");
    connect->setFixedWidth(connect->width() / 2);
    connect->setFixedHeight(45);
    connect->setCursor(QCursor(Qt::PointingHandCursor));

    setFixedSize(this->size());
    setLayout(_mainLayout);
}
