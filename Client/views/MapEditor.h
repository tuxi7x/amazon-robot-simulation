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
#include <QMessageBox>
#include "library/buttons/editor/SideBarButton.h"
#include "library/buttons/editor/EditorGridButton.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QApplication>
#include <QKeyEvent>
#include <QEvent>
#include <QWidget>

/**
 * @brief The MapEditor class is one of the main views of this application. It is responsible
 */
class MapEditor : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief MapEditor Constructor for this class.
     * @param parent The parent of this view.
     */
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();

public slots:
    void openMapEditor(QRect windowPosition);

private slots:
    void onButtonDroppedToMap (int row, int col, SideBarButton* droppedButton);
    void onFieldButtonPressed();
    void onMapCreated();
    void onFieldChanged(int row, int col);
    void onChangeSizeButtonPressed();
    void backButtonPressed();
    void saveButtonPressed();
    void settingOrdersButtonPressed();
    void onShelfSelectionChanged (int row, int col, bool selection);
signals:
    void editorClosed(QRect windowPosition);

protected:
    void keyPressEvent(QKeyEvent*) override;

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
    QPushButton* _settingOrders;
    MapEditorController* _controller;
    QVBoxLayout* _gridContainer;
    QVBoxLayout* _changeSizeContainer;

    QLabel* _changeSizeLabel;
    QLineEdit* _changeSizeLineEdit;
    QPushButton* _changeSizeButton;
    QVector<QVector<EditorGridButton*>> _gridButtons;




};

#endif // MAPEDITOR_H
