#ifndef SIDEBARBUTTON_H
#define SIDEBARBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class SideBarButton : public QPushButton
{
    Q_OBJECT
public:
    SideBarButton(QString text, QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPixmap* _pixmap;
};

#endif // SIDEBARBUTTON_H
