#ifndef SIMULATIONBUTTON_H
#define SIMULATIONBUTTON_H

#include <QPushButton>

class SimulationButton : public QPushButton
{
    Q_OBJECT
public:
    SimulationButton(int row, int col);
    int getRow() { return _row; }
    int getCol() { return _col; }
private:
    int _row;
    int _col;


};

#endif // SIMULATIONBUTTON_H
