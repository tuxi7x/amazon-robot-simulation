#include "EditorGridButton.h"



EditorGridButton::EditorGridButton()
{
    setAcceptDrops(true);
}

void EditorGridButton::dragEnterEvent(QDragEnterEvent *event)
{
    _styleSheet = this->styleSheet();
    setStyleSheet(_styleSheet + "background-color: grey;");
    event->acceptProposedAction();
}

void EditorGridButton::dragMoveEvent(QDragMoveEvent *event)
{
    //TODO implement this
}

void EditorGridButton::dragLeaveEvent(QDragLeaveEvent *event)
{
    setStyleSheet(_styleSheet);
    //TODO implement this
}

void EditorGridButton::dropEvent(QDropEvent *event)
{
    setStyleSheet(_styleSheet + "background-color: green;");
    //TODO implement this
}
