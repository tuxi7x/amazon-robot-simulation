#ifndef EDITORGRIDBUTTON_H
#define EDITORGRIDBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

class EditorGridButton : public QPushButton
{
    Q_OBJECT
public:
    EditorGridButton();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent (QDragLeaveEvent *event) override;
    void dropEvent (QDropEvent *event) override;

private:
    QString _styleSheet;
};

#endif // EDITORGRIDBUTTON_H
