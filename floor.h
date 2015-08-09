#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "constants.h"
#include "chamber.h"

class Cell;

class Floor {
private:
    Cell *cells[ROWS][COLMS];                    // The actual "floor" of Cells
    Chamber *chambers[CHAMBERS];                // The chambers in the floor
    bool connected;                             // The state of cell "self-awareness" of their neighbours
    
    void floodFillHelper(char (*layout)[ROWS][COLMS], Chamber *chamber, int r, int c);    // Prepare the Chamber
    void floodFillChamber(char (*layout)[ROWS][COLMS], Chamber *chamber);                 // Prepare the Chamber
public:
    Floor();
    ~Floor();                                   // Note: Deleting a Floor also deletes its Cells and Chambers
    
    void clearFloor();                          // Removes all occupants from Cells. Does NOT delete them.
    Cell *getCell(int row, int col);            // Get Cell residing at (row, col)
    Chamber *getChamber(int chamberNumber);     // Chamber number between 1 and CHAMBERS
    bool hasConnections();                      // All cells are aware of their neighbours
    void connect();                             // Update self-awareness

    friend std::ostream &operator<<(std::ostream &out, Floor &floor);
};

#endif
