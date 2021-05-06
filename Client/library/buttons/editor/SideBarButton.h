#ifndef SIDEBARBUTTON_H
#define SIDEBARBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

/**
 * @brief The SideBarButton class is a draggable Button which is used to place new elements onto the editor map.
 */
class SideBarButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief SideBarButton A basic constructor for the SideBarButton
     * @param text The text of the SideBarButton
     * @param parent The parent of the SideBarButton
     */
    SideBarButton(QString text, QWidget* parent);

protected:
    /**
     * @brief mousePressEvent Starts the drag and drop action.
     * @param event Contains the information about how this button was pressed.
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPixmap* _pixmap;
};

#endif // SIDEBARBUTTON_H
