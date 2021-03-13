#include "MapEditor.h"

#include "library/dialogs/ErrorDialog.h"
#include "library/dialogs/ProductsOnShelfDialog.h"
#include "library/dialogs/OrderDialog.h"

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
    _saveButton = new QPushButton("Mentés",this);
    _backButton = new QPushButton("Vissza",this);
    _settingOrders = new QPushButton("Rendelések", this);
    _productButton = new SideBarButton("Termék",this);
    _shelfButton = new SideBarButton("Polc",this);
    _dockerButton = new SideBarButton("Dokkoló",this);

    _controller = new MapEditorController();

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
    _sidePanel->addWidget(_settingOrders);
    _sidePanel->addWidget(_saveButton);
    _sidePanel->addWidget(_backButton);

    _changeSizeButton->setFixedSize(QSize(140,30));
    _settingOrders->setFixedSize(QSize(140, 40));
    _saveButton->setFixedSize(QSize(140,40));
    _backButton->setFixedSize(QSize(140,40));
    _productButton->setFixedSize(QSize(140,40));
    _shelfButton->setFixedSize(QSize(140,40));
    _dockerButton->setFixedSize(QSize(140,40));
    _robotButton->setFixedSize(QSize(140,40));
    _dropOffPointButton->setFixedSize(QSize(140,40));
    _changeSizeLineEdit->setFixedSize(QSize(140,27));

    _saveButton->setCursor(QCursor(Qt::PointingHandCursor));
    _backButton->setCursor(QCursor(Qt::PointingHandCursor));
    _changeSizeButton->setCursor(QCursor(Qt::PointingHandCursor));
    _settingOrders->setCursor(QCursor(Qt::PointingHandCursor));

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
    _settingOrders->setStyleSheet("background-color: #8E3FCB; color: white; border: none; font-size:21px;");
    _sidePanel->setSpacing(20);
    _sidePanel->setAlignment(Qt::AlignVCenter);

    _mapGrid->setSpacing(0);

    _centralWidget = new QWidget;
    _centralWidget->setLayout(_mainLayout);
    setCentralWidget(_centralWidget);
    _centralWidget->setStyleSheet("background-color: #118ab2;");

    connect(_controller, &MapEditorController::mapCreated, this, &MapEditor::onMapCreated);
    connect(_controller, &MapEditorController::fieldChanged, this, &MapEditor::onFieldChanged);
    connect(_changeSizeButton, &SideBarButton::pressed, this, &MapEditor::onChangeSizeButtonPressed);
    connect(_backButton, &QPushButton::clicked, this, &MapEditor::backButtonPressed);
    connect(_saveButton, &QPushButton::clicked, this, &MapEditor::saveButtonPressed);
    connect(_settingOrders, &QPushButton::clicked, this, &MapEditor::settingOrdersButtonPressed);
    connect(_controller, &MapEditorController::shelfSelectionChanged, this, &MapEditor::onShelfSelectionChanged);
    _controller->createNewMap(_changeSizeLineEdit->text().toInt());
}

MapEditor::~MapEditor()
{
    QLayoutItem *child;
    while((child = _changeSizeContainer->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
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
    delete _controller;
    delete _centralWidget;
}



void MapEditor::openMapEditor(QRect windowPosition)
{
    setGeometry(windowPosition);
    QMainWindow::show();
}

void MapEditor::onButtonDroppedToMap(int row, int col, SideBarButton *droppedButton)
{
    if(droppedButton == _robotButton) {
        _controller->addRobot(row,col);
    } else if(droppedButton == _dropOffPointButton && _controller->getField(row,col).first == MapEditorController::Empty) {

        QVector<QString> productsToChooseFrom = _controller->getUnassignedProducts();

        if(productsToChooseFrom.isEmpty()) {
            ErrorDialog e ("Jelenleg minden termékhez van célállomás rendelve!");
            e.exec();
            return;
        }
        QInputDialog d;
        d.setLabelText("Melyik termék célállomása legyen?");
        d.setComboBoxItems(productsToChooseFrom);
        d.setWindowTitle("Célállomás hozzáadása");
        if(d.exec()) {
            _controller->addDropOffPoint(row,col, d.textValue());
        }

    } else if (droppedButton == _dockerButton) {
        _controller->addDocker(row,col);
    } else if (droppedButton == _shelfButton) {
        _controller->addShelf(row,col);
    } else if(droppedButton == _productButton) {
        if(_controller->validateProductPlacement(row,col)) {
            bool ok;
            QString name = QInputDialog::getText(this, "Termék neve", "Az új termék neve:", QLineEdit::Normal, "", &ok);
            if(ok && !name.isEmpty()) {
                bool ok = _controller->addProduct(row,col,name);
                if(!ok && !_controller->isASelectedShelf(row,col)) {
                    ErrorDialog e ("A polcon már van ilyen termék!");
                    e.exec();
                } else if(!ok) {
                    ErrorDialog e ("Az egyik kijelölt polcon már van ilyen termék!");
                    e.exec();
                }
            }
        }
        else {
            ErrorDialog e ("Terméket csak polcra lehet helyezni!");
            e.exec();
        }
    }
}

void MapEditor::onFieldButtonPressed()
{
    EditorGridButton* s = qobject_cast<EditorGridButton*> (sender());
    QPair<MapEditorController::FieldTypes, QObject*> res = _controller->getField(s->getRow(), s->getCol());
    if(res.first == MapEditorController::Shelf) {

        //IF shift is pressed then the shelf gets selected, else the dialog opens that shows the products on this shelf
        if(QApplication::keyboardModifiers() == Qt::ShiftModifier) {
            ShelfFieldModel* selectedShelf = qobject_cast<ShelfFieldModel*> (res.second);
            _controller->toggleShelfSelection(selectedShelf);
        } else {
            QVector<QString> productsOnThisShelf = _controller->getProductsOnShelf(s->getRow(), s->getCol());
            ProductsOnShelfDialog posd (productsOnThisShelf);
            posd.exec();
        }
    }

}

void MapEditor::onMapCreated()
{
    int size = _controller->getSize();

    for (int i = 0; i < _mapGrid->count(); i++)
    {
       _mapGrid->itemAt(i)->widget()->deleteLater();
    }

    _gridButtons.clear();

    for (int i=0; i<size; i++) {
        QVector<EditorGridButton*> line;
        for (int j=0; j<size; j++) {
            EditorGridButton* btn = new EditorGridButton(i,j);
            btn->setEmptyButtonStyleSheet();
            connect(btn, &EditorGridButton::buttonDropped, this, &MapEditor::onButtonDroppedToMap);
            connect(btn, &EditorGridButton::clicked, this, &MapEditor::onFieldButtonPressed);
            btn->setFixedSize(QSize(630/size,630/size));
            _mapGrid->addWidget(btn,i,j);
            line.append(btn);
        }
        _gridButtons.append(line);
    }
}

void MapEditor::onFieldChanged(int row, int col)
{
   QPair<MapEditorController::FieldTypes, QObject*> field = _controller->getField(row,col);
   MapEditorController::FieldTypes val = field.first;

   if(val == MapEditorController::Robot) {
       _gridButtons[row][col]->setRobotButtonStyleSheet();
   } else if (val == MapEditorController::Shelf) {
        if(_controller->isASelectedShelf(row,col)) _gridButtons[row][col]->setSelectedShelfButtonStyleSheet();
        else _gridButtons[row][col]->setUnselectedShelfButtonStyleSheet();
       _gridButtons[row][col]->setCursor(QCursor(Qt::PointingHandCursor));
   } else if (val == MapEditorController::DropOffPoint) {
       DropOffPointFieldModel* dopfm = qobject_cast<DropOffPointFieldModel*> (field.second);
       _gridButtons[row][col]->setDropOffPointButtonStyleSheet(dopfm->getProduct());
   } else if(val == MapEditorController::Docker) {
       _gridButtons[row][col]->setDockerButtonStyleSheet();
   } else if (val == MapEditorController::Empty) {
       _gridButtons[row][col]->setEmptyButtonStyleSheet();
       _gridButtons[row][col]->setCursor(QCursor(Qt::ArrowCursor));
   }
}



void MapEditor::onChangeSizeButtonPressed()
{
    _controller->createNewMap(_changeSizeLineEdit->text().toInt());
}

void MapEditor::backButtonPressed()
{
    if(_controller->fieldIsEmpty()) {
        emit editorClosed(this->geometry());
    } else if(QMessageBox::Yes == QMessageBox::question(this, "Vissza?", "Biztosan vissza szeretnél lépni?\nMinden nem mentett változtatás elveszik!", QMessageBox::Yes | QMessageBox::No)) {
        emit editorClosed(this->geometry());
    }

}

void MapEditor::saveButtonPressed()
{
    QString message = _controller->validateBeforeSave();
    if(message!="OK") {
        ErrorDialog e (message);
        e.exec();
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                tr("Szimuláció mentése"), "",
                tr("JSON fájl (*.json);;Minden fájl (*)"));

        if (fileName.isEmpty()) {
            return;
        }


        QFile* file = new QFile(fileName);


        if (_controller->saveToJSON(file)) {
            QMessageBox::information(this, tr("Siker"),
                            tr("Fájl sikeresen mentve."));
        } else {
            QMessageBox::warning(this, tr("Sikertelen mentés"),
                            tr("Nem sikerült menteni a fájlt."));
        }
    }

}

void MapEditor::settingOrdersButtonPressed()
{
    QVector<QString> products = _controller->getProducts();
    QVector<QString> orders = _controller->getOrders();

    OrderDialog od(products, orders);
    if(od.exec()) {
        orders = od.getOrders();
        _controller->setOrders(orders);
    }
}

void MapEditor::onShelfSelectionChanged(int row, int col, bool selection)
{
    if (selection) _gridButtons[row][col]->setSelectedShelfButtonStyleSheet();
    else _gridButtons[row][col]->setUnselectedShelfButtonStyleSheet();
}


void MapEditor:: keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    int direction;

    if(event->key() == 65) { //Letter a
        direction = 3;
    } else if(event->key() == 68) { //letter d
        direction = 1;
    } else if(event->key() == 87) { //letter w
        direction = 0;
    } else if(event->key() == 83) { //letter s
        direction = 2;
    } else return;

    if(!_controller->moveSelectedShelves(direction)) {
        ErrorDialog d ("Valamelyik kijelölt polc nem mozgatható a kívánt irányba, ezért a mozgatás nem hajtható végre!");
        d.exec();
    }

}

