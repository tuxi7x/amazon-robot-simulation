#include "MapEditor.h"

MapEditor::MapEditor(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1024,728);
    setWindowTitle("Szerkesztő felület");
    setWindowIcon(QIcon(":/Resources/resources/logo.png"));

    _mainLayout = new QHBoxLayout();
    _mapGrid = new QGridLayout();
    _sidePanel = new QVBoxLayout();
    _robotButton = new SideBarButton("Robot", this);
    _dropOffPointButton = new SideBarButton("Célállomás",this);
    _saveButton = new SideBarButton("Mentés",this);
    _backButton = new SideBarButton("Vissza",this);
    _productButton = new SideBarButton("Termék",this);
    _shelfButton = new SideBarButton("Polc",this);
    _dockerButton = new SideBarButton("Dokkoló",this);

    _controller = new MapEditorController();
    _buttons = new QVector<QPushButton*>();

    _changeSizeButton = new QPushButton("Beállít");
    _changeSizeLabel = new QLabel("Méret");
    _changeSizeLineEdit = new QLineEdit();

    _gridContainer = new QVBoxLayout();

    _gridContainer->addLayout(_mapGrid);

    _mainLayout->addLayout(_gridContainer);
    _mainLayout->addLayout(_sidePanel);

    _changeSizeContainer = new QVBoxLayout();
    _sidePanel->addLayout(_changeSizeContainer);

    _changeSizeContainer->addWidget(_changeSizeLabel);
    _changeSizeContainer->addWidget(_changeSizeLineEdit);
    _changeSizeContainer->addWidget(_changeSizeButton);
    _changeSizeContainer->setSpacing(8);

    _sidePanel->addWidget(_robotButton);
    _sidePanel->addWidget(_shelfButton);
    _sidePanel->addWidget(_dockerButton);
    _sidePanel->addWidget(_dropOffPointButton);
    _sidePanel->addWidget(_productButton);
    _sidePanel->addWidget(_saveButton);
    _sidePanel->addWidget(_backButton);



    _changeSizeButton->setFixedSize(QSize(140,30));
    _saveButton->setFixedSize(QSize(140,40));
    _backButton->setFixedSize(QSize(140,40));
    _productButton->setFixedSize(QSize(140,40));
    _shelfButton->setFixedSize(QSize(140,40));
    _dockerButton->setFixedSize(QSize(140,40));
    _robotButton->setFixedSize(QSize(140,40));
    _dropOffPointButton->setFixedSize(QSize(140,40));
    _changeSizeLineEdit->setFixedSize(QSize(140,27));

    _changeSizeLineEdit->setText("6");

    _changeSizeLabel->setStyleSheet("color: white; font-size:26px;");
    _changeSizeLineEdit->setStyleSheet("background-color: white; border: none; font-size: 20px;");
    _changeSizeButton->setStyleSheet("background-color: #FFD166; color: white; border-radius: 14px; font-size: 20px;");
    _robotButton->setStyleSheet("background-color: #EF476F; color: white; border: none; font-size:21px;");
    _shelfButton->setStyleSheet("background-color: #06D6A0; color: white; border: none; font-size:21px;");
    _dockerButton->setStyleSheet("background-color: #F26419; color: white; border: none; font-size:21px;");
    _dropOffPointButton->setStyleSheet("background-color: #907F9F; color: white; border: none; font-size:21px;");
    _productButton->setStyleSheet("background-color: #34B1FF; color: white; border: none; font-size:21px;");
    _saveButton->setStyleSheet("background-color: #12DF4B; color: white; border: none; font-size:21px;");
    _backButton->setStyleSheet("background-color: #DF1211; color: white; border: none; font-size:21px;");
    _sidePanel->setSpacing(30);
    _sidePanel->setAlignment(Qt::AlignVCenter);

    _mapGrid->setSpacing(0);



    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            QPushButton* btn = new EditorGridButton();
            btn->setStyleSheet("background-color: white; border: 1px solid black;");
            btn->setFixedSize(QSize(105,105));
            _mapGrid->addWidget(btn,i,j);
        }
    }



    _centralWidget = new QWidget;
    _centralWidget->setLayout(_mainLayout);
    setCentralWidget(_centralWidget);
    _centralWidget->setStyleSheet("background-color: #118ab2;");

}

MapEditor::~MapEditor()
{
    delete _centralWidget;
}

void MapEditor::closeEvent(QCloseEvent *event)
{
    emit editorClosed(this->geometry());
    QMainWindow::closeEvent(event);
}

void MapEditor::openMapEditor(QRect windowPosition)
{
    setGeometry(windowPosition);
    QMainWindow::show();
}



