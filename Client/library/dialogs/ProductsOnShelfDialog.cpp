#include "ProductsOnShelfDialog.h"

ProductsOnShelfDialog::ProductsOnShelfDialog(QVector<QString> products): DialogBase()
{
    setFixedSize(250,250);
    setWindowTitle("A polc termékei");
    _mainLayout = new QVBoxLayout;
    setLayout(_mainLayout);
    _list = new QListWidget;
    _mainLayout->addWidget(_list);
    _list->setStyleSheet("font-size: 15px; background-color:white; font-weight: bold;");
    setModal(true);

    for(int i=0; i<products.size();i++) {
        _list->addItem(products[i]);
    }
    if(_list->count() == 0) _list->addItem("A polc üres!");
}

ProductsOnShelfDialog::~ProductsOnShelfDialog()
{
    QLayoutItem* child;
    while((child = _mainLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete _mainLayout;
}
