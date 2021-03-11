#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>

class SimulationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SimulationWindow(QTcpSocket* connection, QWidget *parent = nullptr);

signals:

private:
    QTcpSocket* _connection;
    QWidget* _centralWidget;
    QHBoxLayout* _mainLayout;
    QGridLayout* _mapGrid;
    QVBoxLayout* _sidePanel;
    QVBoxLayout* _gridContainer;
    QPushButton* _newOrderButton;
    QPushButton* _pauseResumeButton;
    QPushButton* _finishSimButton;
    QPushButton* _disconnectButton;
    void createMap();

};

#endif // SIMULATIONWINDOW_H
