#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include "controllers/Connection.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class SimulationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SimulationWindow(Connection* connection, QWidget *parent = nullptr);
    ~SimulationWindow();

signals:
    void simulationClosed(QRect pos);

private:
    QVector<QVector<QPushButton*>> _buttons;
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
    void onFieldToDropOffSignal (int row, int col);
    void onFieldtoDockerSignal (int row, int col);
    void onGameSpeedChangedSignal (int newSpeed);
    void onPauseStateChangedSignal (bool paused);
    void onPauseResumeButtonClicked();

};

#endif // SIMULATIONWINDOW_H
