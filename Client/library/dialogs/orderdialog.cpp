#include "OrderDialog.h"
#include "QDebug"

OrderDialog::OrderDialog(QVector<QString> products, QVector<QString> orders) : DialogBase()
{
    setFixedSize(500,500);
    setWindowTitle("Rendelések");
    _layout = new QGridLayout;
    _flayout = new QFormLayout;

    setLayout(_layout);
    _productLabel = new QLabel("Felhelyezett termékek:");
    _orderLabel = new QLabel("Rendelésre kiválasztva:");
    _productList = new QListWidget;
    _orderList = new QListWidget;
    _add = new QPushButton(">");
    _remove = new QPushButton("<");
    _ok = new QPushButton("Oké");

    _layout->addWidget(_productLabel, 0, 0);
    _layout->addWidget(_orderLabel, 0, 2);
    _layout->addWidget(_productList, 1, 0);
    _layout->addWidget(_orderList, 1, 2);
    _flayout->addWidget(_add);
    _flayout->addWidget(_remove);
    _layout->addLayout(_flayout, 1, 1);
    _layout->addWidget(_ok, 2, 2);

    _productList->setStyleSheet("font-size: 15px; background-color:white;");
    _orderList->setStyleSheet("font-size: 15px; background-color:white;");
    _add->setStyleSheet("background-color:white; font-weight: bold;");
    _remove->setStyleSheet("background-color:white; font-weight: bold;");
    _ok->setStyleSheet("background-color:white; font-weight: bold;");
    _productLabel->setStyleSheet("font-weight: bold;");
    _orderLabel->setStyleSheet("font-weight: bold;");
    setModal(true);


    for(int i=0; i<products.size();i++) {
        if(!orders.contains(products[i])) {
            _productList->addItem(products[i]);
            _products.append(products[i]);
        } else {
            _orderList->addItem(orders[i]);
            _orders.append(products[i]);

        }

    }
    if(_productList->count() == 0 && _orderList->count() == 0) _productList->addItem("Még nem lett termék felhelyezve.");

    connect(_add, &QPushButton::clicked, this, &OrderDialog::addButtonPressed);
    connect(_remove, &QPushButton::clicked, this, &OrderDialog::removeButtonPressed);
    connect(_ok, &QPushButton::clicked, this, &OrderDialog::okButtonPressed);
    connect(_productList, &QListWidget::itemDoubleClicked, this, &OrderDialog::productDoubleClicked);
    connect(_orderList, &QListWidget::itemDoubleClicked, this, &OrderDialog::orderDoubleClicked);
}
OrderDialog::~OrderDialog()
{
    delete _add;
    delete _remove;

    QLayoutItem *child;
    while((child = _layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _layout;

}

QVector<QString> OrderDialog::getOrders()
{
    return _orders;
}

void OrderDialog::addButtonPressed()
{
    if(_products.length() != 0){
    QListWidgetItem* selected = _productList->takeItem(_productList->currentRow());
    _orderList->addItem(selected);
    update();
    }
}

void OrderDialog::removeButtonPressed()
{
    if(_products.length() != 0){
    QListWidgetItem* selected = _orderList->takeItem(_orderList->currentRow());
    _productList->addItem(selected);
    update();
    }
}

void OrderDialog::okButtonPressed()
{
    _orders.clear();
    int i = 0;
    while(_orderList->item(i) != nullptr){
        _orders.append(_orderList->item(i)->text());
        i++;
    }

    accept();
}

void OrderDialog::productDoubleClicked()
{
    if(_products.length() != 0){
    QListWidgetItem* selected = _productList->takeItem(_productList->currentRow());
    _orderList->addItem(selected);
    update();
    }
}

void OrderDialog::orderDoubleClicked()
{
    if(_orders.length() != 0){
    QListWidgetItem* selected = _orderList->takeItem(_orderList->currentRow());
    _productList->addItem(selected);
    update();
    }
}
