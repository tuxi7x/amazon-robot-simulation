#include "EditorGridButton.h"



EditorGridButton::EditorGridButton(int row, int col) : QPushButton(), _row(row), _col(col)
{
    setStyleSheet("background-color: white; border: 1px solid black;");
    setAcceptDrops(true);
}

void EditorGridButton::setEmptyButtonStyleSheet()
{
    setStyleSheet("background-color: white; color:white; font-size: 30px; border: 1px solid black;");
    setText("");
}

void EditorGridButton::setRobotButtonStyleSheet()
{
    setStyleSheet("background-color: #ef476e; color:white; font-size: 30px; border: 1px solid black;");
    setText("R");
}

void EditorGridButton::setDockerButtonStyleSheet()
{
    setStyleSheet("background-color: #f26419; color:white; font-size: 30px; border: 1px solid black;");
    setText("D");
}

void EditorGridButton::setUnselectedShelfButtonStyleSheet()
{
    setStyleSheet("background-color: #06d6a0; color:white; font-size: 30px; border: 1px solid black;");
    setText("P");
}

void EditorGridButton::setSelectedShelfButtonStyleSheet()
{
    setStyleSheet("background-color: #06d6a0; color:white; font-size: 30px; border: 5px solid black;");
    setText("P");
}

void EditorGridButton::setDropOffPointButtonStyleSheet(QString product)
{
    setStyleSheet("background-color: #907f9f; color:white; font-size: 30px; border: 1px solid black;");
    setText("C\n(" + product + ")");
}

void EditorGridButton::dragEnterEvent(QDragEnterEvent *event)
{
   QPointer<QObject> item = event->mimeData()->parent();

   if(item)
   {
       _styleSheet = this->styleSheet();
       event->acceptProposedAction();
       setStyleSheet(_styleSheet + "background-color: grey;");
   }

}


void EditorGridButton::dragLeaveEvent(QDragLeaveEvent *event)
{
    setStyleSheet(_styleSheet);
    QPushButton::dragLeaveEvent(event);
}

void EditorGridButton::dropEvent(QDropEvent *event)
{
    setStyleSheet(_styleSheet);
    SideBarButton* droppedButton = qobject_cast<SideBarButton*>(event->mimeData()->parent());
    emit buttonDropped(_row,_col,droppedButton);
}


int EditorGridButton::getCol() const
{
    return _col;
}

int EditorGridButton::getRow() const
{
    return _row;
}
