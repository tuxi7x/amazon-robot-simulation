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

    QVector<QString> alreadyOrdered;
    for(int i = 0; i<orders.length(); i++){
        alreadyOrdered.append(orders[i]);
    }

    QVector<ProductModel*> productsToList;
    for(int i = 0; i<products.length(); i++){
        productsToList.append(products[i]);
    }
    qDebug() << "for elott";
    for(int i = 0; i<productsToList.length(); i++){
        int j = 0;
        while(j < alreadyOrdered.length()  && !productsToList.isEmpty() && !alreadyOrdered.isEmpty()) {
            qDebug() << "while belul";
            if(productsToList[i]->getName() == alreadyOrdered[j]){
                qDebug() << "if belul";
                productsToList.erase(std::find(productsToList.begin(),productsToList.end(),productsToList[i]));
                qDebug() << "torles kozott belul";
                alreadyOrdered.erase(std::find(alreadyOrdered.begin(),alreadyOrdered.end(),alreadyOrdered[j]));
                continue;
            }else j++;
        }
    }
    for(int i=0; i<productsToList.length();i++) {
        _productList->addItem(productsToList[i]->getName());
        _products.append(productsToList[i]);
        }


    if(_productList->count() == 0 && _orderList->count() == 0) _productList->addItem("Jelenleg nincs rendelhető termék készleten.");

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
    return _newOrders;
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
    if(_products.length() != 0){
    QListWidgetItem* selected = _productList->takeItem(_productList->currentRow());
    _orderList->addItem(selected);
    update();
    }
}

void NewOrderDialog::orderDoubleClicked()
{
    if(_newOrders.length() != 0){
    QListWidgetItem* selected = _orderList->takeItem(_orderList->currentRow());
    _productList->addItem(selected);
    update();
    }
}
