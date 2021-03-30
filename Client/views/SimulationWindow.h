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
    void createMap();



};

#endif // SIMULATIONWINDOW_H
