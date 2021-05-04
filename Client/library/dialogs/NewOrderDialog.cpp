#include "NewOrderDialog.h"

NewOrderDialog::NewOrderDialog(QVector<ProductModel*> products, QVector<QString> orders) : DialogBase()
{
    setFixedSize(500,500);
    setWindowTitle("Rendelések");
    _layout = new QGridLayout;
    _flayout = new QFormLayout;

    setLayout(_layout);
    _productLabel = new QLabel("Készleten levő termékek:");
    _orderLabel = new QLabel("Kosár - rendelésre kiválasztva:");
    _productList = new QListWidget;
    _orderList = new QListWidget;
    _ok = new QPushButton("Oké");

    _layout->addWidget(_productLabel, 0, 0);
    _layout->addWidget(_orderLabel, 0, 2);
    _layout->addWidget(_productList, 1, 0);
    _layout->addWidget(_orderList, 1, 2);
    _layout->addLayout(_flayout, 1, 1);
    _layout->addWidget(_ok, 2, 2);

    _productList->setStyleSheet("font-size: 15px; background-color:white;");
    _orderList->setStyleSheet("font-size: 15px; background-color:white;");
    _ok->setStyleSheet("background-color:white; font-weight: bold;");
    _productLabel->setStyleSheet("font-weight: bold;");
    _orderLabel->setStyleSheet("font-weight: bold;");
    setModal(true);
    QVector<QString> pr;



    for(int i = 0; i< products.length(); i++)
        {
        qInfo() << products[i]->getName() << " ";
        pr.append(products[i]->getName());
    }
    for(int i=0; i<orders.length();i++) {
            int k = pr.indexOf(orders[i]);
            if (k != -1)
                pr.remove(k);
    }

    for(int i=0; i<pr.length();i++) {
        _productList->addItem(pr[i]);
        _pr.append(pr[i]);
    }
    if(_productList->count() == 0 ) _productList->addItem("Jelenleg nincs rendelhető termék készleten.");

    connect(_ok, &QPushButton::clicked, this, &NewOrderDialog::okButtonPressed);
    connect(_productList, &QListWidget::itemDoubleClicked, this, &NewOrderDialog::productDoubleClicked);
}

NewOrderDialog::~NewOrderDialog()
{
    QLayoutItem *child;
    while((child = _layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _layout;
}

QVector<QString> NewOrderDialog::getOrders()
{
    QVector<QString> l;

    for(int j=0; j<_newOrders.size();j++) {
            l.append(_newOrders[j]);
    }
    return l;
}


void NewOrderDialog::okButtonPressed()
{
    _newOrders.clear();
    int i = 0;
    while(_orderList->item(i) != nullptr){
        _newOrders.append(_orderList->item(i)->text());
        i++;
    }

    accept();
}

void NewOrderDialog::productDoubleClicked()
{
    if(_pr.length() != 0){
    QListWidgetItem* selected = _productList->takeItem(_productList->currentRow());
    _orderList->addItem(selected);
    update();
    }
}

