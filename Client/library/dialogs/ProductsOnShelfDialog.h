#ifndef PRODUCTSONSHELFDIALOG_H
#define PRODUCTSONSHELFDIALOG_H

#include "DialogBase.h"
#include <QListWidget>
#include <QObject>

/**
 * @brief The ProductsOnShelfDialog class A special Dialog class used to show the user the content of a shelf during simulation and during map editing.
 */
class ProductsOnShelfDialog : public DialogBase
{
    Q_OBJECT
public:
    /**
     * @brief ProductsOnShelfDialog Constructor for this class.
     * @param products The products on this shelf.
     */
    ProductsOnShelfDialog(QVector<QString> products);
    ~ProductsOnShelfDialog();

private:
    QListWidget* _list;
};

#endif // PRODUCTSONSHELFDIALOG_H
