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
#include <QPaintEvent>

/**
 * @brief The EditorGridButton class is a special QPushButton that is only used in the grid of the Editor window.
 * It is mainly used to correctly handle drag and drop actions, but it implements switching stylesheets of this button.
 * It stores the row of the column of this button in the editor grid.
 */
class EditorGridButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief EditorGridButton A constructor for the EditorGridButton that only takes in the row and the column of this button.
     * @param row The row of the button.
     * @param col The column of the button.
     */
    EditorGridButton(int row, int col);
    /**
     * @brief setEmptyButtonStyleSheet Sets the stylesheet of this button to represent an empty field.
     */
    void setEmptyButtonStyleSheet();
    /**
     * @brief setRobotButtonStyleSheet Sets the stylesheet of this button to represent a field with a Robot on it.
     */
    void setRobotButtonStyleSheet();
    /**
     * @brief setDockerButtonStyleSheet Sets the stylesheet of this button to represent a field with a Docker on it.
     */
    void setDockerButtonStyleSheet();
    /**
     * @brief setUnselectedShelfButtonStyleSheet Sets the stylesheet of this button to represent a field with an unselected shelf on it.
     */
    void setUnselectedShelfButtonStyleSheet();
    /**
     * @brief setSelectedShelfButtonStyleSheet Sets the stylesheet of this button to represent a field with a selected shelf on it.
     */
    void setSelectedShelfButtonStyleSheet();
    /**
     * @brief setDropOffPointButtonStyleSheet Sets the stylesheet of this button to represent a field with a drop off point on it.
     */
    void setDropOffPointButtonStyleSheet(QString product);
    /**
     * @brief setRobotOrientation Sets the direction of the robot on this field.
     * @param orientation The new orientation of the robot. 0 = north, 1 = east, 2 = south, 3 = west
     */
    void setRobotOrientation(int orientation);
    /**
     * @brief getRow A getter for the row of the Robot
     * @return Returns the row of the Robot as an int.
     */
    int getRow() const;
    /**
     * @brief getRow A getter for the row of the Robot
     * @return Returns the row of the Robot as an int.
     */
    int getCol() const;

protected:
    /**
     * @brief dragEnterEvent Paints the Button grey when a button has been dragged onto it.
     * @param event The QDragEnterEvent contains the information about the specific drag.
     */
    void dragEnterEvent(QDragEnterEvent* event) override;
    /**
     * @brief dragLeaveEvent Paints the Button back to normal when a dragged Button leaves the area of this Button.
     * @param event QDragLeaveEvent contains the information about the specific drag.
     */
    void dragLeaveEvent (QDragLeaveEvent *event) override;
    /**
     * @brief dropEvent Handles the event when a SideBarButton has been dropped onto this Button.
     * @param event QDropEvent containts the information about the specific drag.
     */
    void dropEvent (QDropEvent *event) override;

private:
    QString _styleSheet;
    int _row;
    int _col;

signals:
    /**
     * @brief buttonDropped This signal gets called when a SideBarButton gets dropped onto this Button.
     * @param row The row of this button
     * @param col The column of this button
     * @param droppedButton The SideBarButton that was dropped.
     */
    void buttonDropped(int row, int col, SideBarButton* droppedButton);
};

#endif // EDITORGRIDBUTTON_H
