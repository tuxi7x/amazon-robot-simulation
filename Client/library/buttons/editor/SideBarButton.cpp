#include "SideBarButton.h"

#include <QDrag>
#include <QMimeData>
#include <QPainter>

SideBarButton::SideBarButton(QString text, QWidget *parent) : QPushButton(text,parent)
{

}

void SideBarButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
       _pixmap = new QPixmap(this->size());
       this->render(_pixmap);

       QDrag* drag = new QDrag(parentWidget());
       drag->setPixmap(*_pixmap);
       QMimeData* mimeData = new QMimeData();
       mimeData->setParent(this);
       drag->setMimeData(mimeData);
       drag->exec();
    }
}
