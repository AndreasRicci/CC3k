#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include <vector>

class Cell;

class Chamber {
private:
    std::vector<Cell *> cells;                  // The Cells that make up this Chamber
public:
    Cell *getNthCell(int n);                    // Get a Cell
    void addCell(Cell *cell);                   // Adds a Cell to this Chamber
    int chamberSize();                          // How many Cells are in this Chamber?
};

#endif
