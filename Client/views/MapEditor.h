#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "../controllers/MapEditorController.h"
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include "library/buttons/editor/SideBarButton.h"
#include "library/buttons/editor/EditorGridButton.h"

class MapEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();

protected:
    void closeEvent(QCloseEvent *event) override;


private:
    QWidget* _centralWidget;

    QHBoxLayout* _mainLayout;
    QGridLayout* _mapGrid;
    QVBoxLayout* _sidePanel;
    SideBarButton* _robotButton;
    SideBarButton* _shelfButton;
    SideBarButton* _dockerButton;
    SideBarButton* _dropOffPointButton;
    SideBarButton* _productButton;
    QPushButton* _saveButton;
    QPushButton* _backButton;
    MapEditorController* _controller;
    QVector<QPushButton*>* _buttons;
    QVBoxLayout* _gridContainer;
    QVBoxLayout* _changeSizeContainer;

    QLabel* _changeSizeLabel;
    QLineEdit* _changeSizeLineEdit;
    QPushButton* _changeSizeButton;
    QVector<QVector<EditorGridButton*>> _gridButtons;


public slots:
    void openMapEditor(QRect windowPosition);

private slots:
    void onButtonDroppedToMap (int row, int col, SideBarButton* droppedButton);
    void onMapCreated();
    void onFieldChanged(int row, int col);
    void onChangeSizeButtonPressed();

signals:
    void editorClosed(QRect windowPosition);


};

#endif // MAPEDITOR_H
