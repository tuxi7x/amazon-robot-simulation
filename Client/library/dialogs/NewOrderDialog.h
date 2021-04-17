#ifndef NEWORDERDIALOG_H
#define NEWORDERDIALOG_H

#include <QObject>
#include "DialogBase.h"
#include "QListWidget"
#include "QPushButton"
#include "QFormLayout"
#include "QLabel"
#include "models/ProductModel.h"



class NewOrderDialog : public DialogBase
{
    Q_OBJECT
public:
    NewOrderDialog(QVector<ProductModel*> products, QVector<QString> orders);
    ~NewOrderDialog();
    QVector<QString> getOrders();

    private:
    QListWidget* _productList;
    QListWidget* _orderList;
    QPushButton* _ok;
    QGridLayout* _layout;
    QFormLayout* _flayout;
    QVector<ProductModel*> _products;
    QVector<QString> _pr;
    QVector<QString> _newOrders;
    QLabel* _productLabel;
    QLabel* _orderLabel;


private slots:
    void okButtonPressed();
    void productDoubleClicked();
};

#endif // NEWORDERDIALOG_H
