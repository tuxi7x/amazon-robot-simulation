#include "StartSimFromFileDialog.h"

StartSimFromFileDialog::StartSimFromFileDialog(Connection *connection)
{
    _connection = connection;
    _file = nullptr;
    _timer = new QTimer;
    _timer->setInterval(10000);
    setWindowTitle("Szimuláció indítása fájlból betöltve");

    _ipLabel = new QLabel("Szerver IP címe");
    _ipBox = new QLineEdit();
    QRegularExpression ipregex ("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    QRegularExpressionValidator* ipValidator = new QRegularExpressionValidator (ipregex);
    _ipBox->setValidator(ipValidator);

    _portLabel = new QLabel("Port");
    _portBox = new QLineEdit();
    _connectButton = new QPushButton("Csatlakozás");
    _browseFileLabel = new QLabel ("Fájl tallózása");

    _browseFileLine = new QHBoxLayout();
    _browseFileButton = new QPushButton("Megnyitás");
    _browseFileButton->setFixedSize(150,50);
    _browseFileButton->setStyleSheet("background-color: white; border-radius: 10px; color: black; font-weight: bold;");
    _browseFileButton->setCursor(QCursor(Qt::PointingHandCursor));
    _selectedFileLabel = new QLabel ("Nincs kiválasztott fájl");
    _selectedFileLabel->setStyleSheet("font-size: 15px");
    _browseFileLine->addWidget(_browseFileButton);
    _browseFileLine->addWidget(_selectedFileLabel);
    _browseFileLine->setSpacing(20);

    _mainLayout = new QVBoxLayout();
    _mainLayout->setSpacing(10);
    _mainLayout->addWidget(_ipLabel);
    _mainLayout->addWidget(_ipBox);
    _mainLayout->addWidget(_portLabel);
    _mainLayout->addWidget(_portBox);
    _mainLayout->addWidget(_browseFileLabel);
    _mainLayout->addLayout(_browseFileLine);
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

    _indicator = new QLabel();
    _indicator->setFixedSize(70,70);
    _mainLayout->addWidget(_indicator);
    _mainLayout->setAlignment(_indicator,Qt::AlignHCenter);
    _progressGif = new QMovie(":/Resources/resources/loadingbar.gif");
    _progressGif->setScaledSize(QSize(70,70));

    setFixedSize(this->size());
    setLayout(_mainLayout);

    connect(_connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));
    connect(_browseFileButton,SIGNAL(clicked()),this,SLOT(browseButtonPressed()));
    connect(_connection,SIGNAL(connected()), this, SLOT(onConnected()));
    connect(_timer, SIGNAL(timeout()),this,SLOT(connectionTimedOut()));


}

StartSimFromFileDialog::~StartSimFromFileDialog()
{
    QLayoutItem* child;
    while((child = _mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _file;
    delete _mainLayout;
}

void StartSimFromFileDialog::connectButtonPressed()
{
    QString ip = _ipBox->text();
    int port = _portBox->text().toInt();

    if (_file != nullptr && _ipBox->text() != "" && _portBox->text() != "" ) {
        _indicator->setMovie(_progressGif);
        _progressGif->start();
        _timer->start();
        _connection->connectAndSend(ip,port,_file);
    } else if (_file == nullptr) {
        ErrorDialog e ("Először ki kell választani egy pályát!");
        e.exec();
    } else {
        ErrorDialog e ("Először meg kell adni az ip címet és a portot!");
        e.exec();
    }
}

void StartSimFromFileDialog::onConnected() {
    accept();
}

void StartSimFromFileDialog::connectionTimedOut()
{
    _progressGif->stop();
    _indicator->setMovie(nullptr);
    ErrorDialog* errorDialog = new ErrorDialog("<b>Hiba:</b><br>A csatlakozás sikertelen (Időtúllépés)!");
    errorDialog->setModal(true);
    errorDialog->exec();
}

void StartSimFromFileDialog::browseButtonPressed()
{

    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("JSON fájl (*.json)"));
    fileDialog.setWindowTitle("Pálya betöltése");

    if(fileDialog.exec()) {
        QStringList files = fileDialog.selectedFiles();
        _file = new QFile(files[0]);
        QFileInfo fileinfo (files[0]);
        _selectedFileLabel->setText(fileinfo.fileName());

        //TODO implement features here

    }


}
