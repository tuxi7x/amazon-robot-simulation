#include "OrderDialog.h"
#include "QDebug"

OrderDialog::OrderDialog(QVector<QString> products, QVector<QString> orders) : DialogBase()
{
    setFixedSize(500,500);
    setWindowTitle("Rendelések");
    _layout = new QGridLayout;
    _flayout = new QFormLayout;

    setLayout(_layout);
    _productList = new QListWidget;
    _orderList = new QListWidget;
    _add = new QPushButton(">");
    _remove = new QPushButton("<");
    _ok = new QPushButton("Oké");

    _layout->addWidget(_productList, 0, 0);
    _layout->addWidget(_orderList, 0, 2);
    _flayout->addWidget(_add);
    _flayout->addWidget(_remove);
    _layout->addLayout(_flayout, 0, 1);
    _layout->addWidget(_ok, 1, 2);

    _productList->setStyleSheet("font-size: 15px; background-color:white;");
    _orderList->setStyleSheet("font-size: 15px; background-color:white;");
    _add->setStyleSheet("background-color:white; font-weight: bold;");
    _remove->setStyleSheet("background-color:white; font-weight: bold;");
    _ok->setStyleSheet("background-color:white; font-weight: bold;");
    setModal(true);


    for(int i=0; i<products.size();i++) {
        _productList->addItem(products[i]);
        _products.append(products[i]);
    }
    if(_productList->count() == 0) _productList->addItem("Még nem lett termék felhelyezve.");

    connect(_add, &QPushButton::clicked, this, &OrderDialog::addButtonPressed);
    connect(_remove, &QPushButton::clicked, this, &OrderDialog::removeButtonPressed);
    connect(_ok, &QPushButton::clicked, this, &OrderDialog::okButtonPressed);
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
    QVector<QString> orders;
    int i = 0;
    while(_orderList->item(i) != nullptr){
        orders.append(_orderList->item(i)->text());
        i++;
    }

    this->close();
}
