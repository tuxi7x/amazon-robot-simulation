#ifndef EDITORGRIDBUTTON_H
#define EDITORGRIDBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include "library/buttons/editor/SideBarButton.h"
#include <QMimeData>

class EditorGridButton : public QPushButton
{
    Q_OBJECT
public:
    EditorGridButton(int row, int col);
    void setEmptyButtonStyleSheet();
    void setRobotButtonStyleSheet();
    void setDockerButtonStyleSheet();
    void setShelfButtonStyleSheet();
    void setDropOffPointButtonStyleSheet();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent (QDragLeaveEvent *event) override;
    void dropEvent (QDropEvent *event) override;

private:
    QString _styleSheet;
    int _row;
    int _col;

signals:
    void buttonDropped(int row, int col, SideBarButton* droppedButton);


};

#endif // EDITORGRIDBUTTON_H
