#include "EditorGridButton.h"



EditorGridButton::EditorGridButton(int row, int col) : QPushButton(), _row(row), _col(col)
{
    setAcceptDrops(true);
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
