#include "RobotInfoDialog.h"

RobotInfoDialog::RobotInfoDialog(int battery)
{
    setFixedSize(250,250);
    setWindowTitle("A robot töltöttsége:");
    _mainLayout = new QVBoxLayout;
    setLayout(_mainLayout);
    _list = new QListWidget;
    _mainLayout->addWidget(_list);
    _list->setStyleSheet("font-size: 15px; background-color:white; font-weight: bold;");
    setModal(true);
    _list->addItem(QString::number(battery));

}
