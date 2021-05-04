#ifndef SIMULATIONBUTTON_H
#define SIMULATIONBUTTON_H

#include <QPushButton>

/**
 * @brief The SimulationButton class is a special QPushButton that is only used in the grid of the simulation window.
 * It contains two extra bit of information: the row and the column of the Button in the grid.
 */
class SimulationButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief SimulationButton Constructor for SimulationButton that only takes in the row and the column as a parameter.
     * @param row The row of the Button in the grid.
     * @param col The column of the Button in the grid.
     */
    SimulationButton(int row, int col);
    /**
     * @brief getRow A getter for the row of the SimulationButton
     * @return the row as an int.
     */
    int getRow() { return _row; }
    /**
     * @brief getCol A getter for the column of the SimulationButton
     * @return the column as an int.
     */
    int getCol() { return _col; }
private:
    int _row;
    int _col;


};

#endif // SIMULATIONBUTTON_H
