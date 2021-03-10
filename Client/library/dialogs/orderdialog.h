#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QObject>
#include "DialogBase.h"
#include "QListWidget"
#include "QPushButton"
#include "QFormLayout"

class OrderDialog : public DialogBase
{
    Q_OBJECT
public:
    explicit OrderDialog(QVector<QString> products, QVector<QString> orders);

    private:
    QListWidget* _productList;
    QListWidget* _orderList;
    QPushButton* _add;
    QPushButton* _remove;
    QPushButton* _ok;
    QGridLayout* _layout;
    QFormLayout* _flayout;
    QVector<QString> _products;
private slots:
    void addButtonPressed();
    void removeButtonPressed();
    void okButtonPressed();
};

#endif // ORDERDIALOG_H
