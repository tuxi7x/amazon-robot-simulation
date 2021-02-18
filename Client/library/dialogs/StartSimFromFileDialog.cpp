#include "StartSimFromFileDialog.h"

StartSimFromFileDialog::StartSimFromFileDialog()
{
    setWindowTitle("Szimuláció indítása fájlból betölve");

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

    setFixedSize(this->size());
    setLayout(_mainLayout);

    connect(_connectButton,SIGNAL(clicked()),this,SLOT(connectButtonPressed()));
    connect(_browseFileButton,SIGNAL(clicked()),this,SLOT(browseButtonPressed()));


}

StartSimFromFileDialog::~StartSimFromFileDialog()
{
    for(int i=0; i< _browseFileLine->count(); i++) {
        delete _browseFileLine->itemAt(i);
    }

    for (int i = 0;i < _mainLayout->count() ; i++ ) {
        delete _mainLayout->itemAt(i);
    }
    delete _mainLayout;
}

void StartSimFromFileDialog::connectButtonPressed()
{

}

void StartSimFromFileDialog::browseButtonPressed()
{

    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("Szövegfájl (*.txt)"));
    fileDialog.setWindowTitle("Pálya betöltése");

    if(fileDialog.exec()) {
        QStringList files = fileDialog.selectedFiles();
        QFile file(files[0]);
        QFileInfo fileinfo (file);
        _selectedFileLabel->setText(fileinfo.fileName());

        //TODO implement features here

    }


}
