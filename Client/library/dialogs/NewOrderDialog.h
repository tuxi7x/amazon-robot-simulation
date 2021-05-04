#ifndef NEWORDERDIALOG_H
#define NEWORDERDIALOG_H

#include <QObject>
#include "DialogBase.h"
#include "QListWidget"
#include "QPushButton"
#include "QFormLayout"
#include "QLabel"
#include "models/ProductModel.h"


/**
 * @brief The NewOrderDialog class The dialog used by the simulation window in order for the user to make online orders of the products available.
 */
class NewOrderDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief NewOrderDialog The constructor for this class.
     * @param products The products on the shelves.
     * @param orders The products that are not available because they are already ordered.
     */
    NewOrderDialog(QVector<ProductModel*> products, QVector<QString> orders);
    ~NewOrderDialog();
    /**
     * @brief getOrders A getter for the new orders selected in this dialog.
     * @return The list of the orders as a QVector containing QString.
     */
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
