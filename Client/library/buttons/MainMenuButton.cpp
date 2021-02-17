#include "MainMenuButton.h"




MainMenuButton::MainMenuButton(const QString &text, QWidget *parent): QPushButton(parent)
{
    setText(text);
    setFixedSize(600,55);
    setStyleSheet("background-color: #ffd166; border-radius: 25px; font-size: 20px; font-weight: bold;");
    setCursor(QCursor(Qt::PointingHandCursor));
}
