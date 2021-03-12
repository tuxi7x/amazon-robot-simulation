#ifndef PRODUCTSONSHELFDIALOG_H
#define PRODUCTSONSHELFDIALOG_H

#include "DialogBase.h"
#include <QListWidget>
#include <QObject>

class ProductsOnShelfDialog : public DialogBase
{
    Q_OBJECT
public:
    ProductsOnShelfDialog(QVector<QString> products);
    ~ProductsOnShelfDialog();

private:
    QListWidget* _list;
};

#endif // PRODUCTSONSHELFDIALOG_H
