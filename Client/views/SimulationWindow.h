#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include "controllers/Connection.h"
#include "library/dialogs/ProductsOnShelfDialog.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include "library/buttons/SimulationButton.h"
#include "library/dialogs/RobotInfoDialog.h"
#include "library/dialogs/NewOrderDialog.h"
#include <QStatusBar>

/**
 * @brief The SimulationWindow class One of the main views of the application. Displays the simulation itself, with the grid and some side buttons.
 */
class SimulationWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief SimulationWindow Constructor for this class.
     * @param connection The connection of the application as dependency injection.
     * @param parent parent of this QWidget.
     */
    explicit SimulationWindow(Connection* connection, QWidget *parent = nullptr);
    ~SimulationWindow();

signals:
    void simulationClosed(QRect pos);

private:
    QVector<QVector<SimulationButton*>> _buttons;
    Connection* _connection;
    QWidget* _centralWidget;
    QHBoxLayout* _mainLayout;
    QGridLayout* _mapGrid;
    QVBoxLayout* _sidePanel;
    QVBoxLayout* _gridContainer;
    QLabel* _speedLabel;
    QSlider* _speedSlider;
    QPushButton* _newOrderButton;
    QPushButton* _pauseResumeButton;
    QPushButton* _finishSimButton;
    QPushButton* _disconnectButton;
    bool _paused;
    void createMap();

private slots:
    void onCreateMapSignal (int size);
    //Orientations: 0 = up, 1 = right, 2 = down, 3 = left
    void onFieldToRobotSignal (int row, int col, int orientation, int battery);
    void onFieldToEmptySignal (int row, int col);
    void onFieldToShelfSignal (int row, int col);
    void onFieldToDropOffSignal (int row, int col, QString product);
    void onFieldtoDockerSignal (int row, int col);
    void onGameSpeedChangedSignal (int newSpeed);
    void onPauseStateChangedSignal (bool paused);
    void onPauseResumeButtonClicked();
    void onFieldButtonPressed();
    void onFinishButtonClicked();
    void onDisconnectButtonClicked();
    void onNewOrderButtonClicked();
    void onSpeedSliderValueChanged();

};

#endif // SIMULATIONWINDOW_H
