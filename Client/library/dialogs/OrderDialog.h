#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QObject>
#include "DialogBase.h"
#include "QListWidget"
#include "QPushButton"
#include "QFormLayout"
#include "QLabel"

/**
 * @brief The OrderDialog class A special dialog class used by the editor to allow setting the orders that are already made at the start of the simulation.
 */
class OrderDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief OrderDialog The constructor for this class.
     * @param products The products on the shelves.
     * @param orders The products that are not available because they are already ordered.
     */
    explicit OrderDialog(QVector<QString> products, QVector<QString> orders);
    ~OrderDialog();
    /**
     * @brief getOrders A getter for the new orders selected in this dialog.
     * @return The list of the orders as a QVector containing QString.
     */
    QVector<QString> getOrders();

    private:
    QListWidget* _productList;
    QListWidget* _orderList;
    QPushButton* _add;
    QPushButton* _remove;
    QPushButton* _ok;
    QGridLayout* _layout;
    QFormLayout* _flayout;
    QVector<QString> _products;
    QVector<QString> _orders;
    QLabel* _productLabel;
    QLabel* _orderLabel;


private slots:
    void addButtonPressed();
    void removeButtonPressed();
    void okButtonPressed();
    void productDoubleClicked();
    void orderDoubleClicked();
};

#endif // ORDERDIALOG_H
