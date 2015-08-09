#ifndef __CELL_H__
#define __CELL_H__

#include <vector>
#include <ostream>

#include "constants.h"

class GameObject;

class Cell {
private:
    char appearance;                            // What the Cell looks like
    std::vector<Cell *> neighbours;             // The Cells immediately surrounding this one
    GameObject *occupant;                       // What currently occupies this Cell (NULL means nothing is)
    #ifdef DLC 
    bool isEdge;
    #endif
public:
    Cell(char appearance = DISPLAY_CELLS[FLOOR]);
    ~Cell();
    #ifdef DLC
    void setEdge(bool edge);
    bool getEdge();
    #endif
    char getAppearance();                       // Get what the Cell looks like
    void setAppearance(char newAppearance);     // What should the Cell look like?
    void addNeighbour(Cell *newNeighbour);      // Add to the Cells considered immediately surrounding
    std::vector<Cell *> getNeighbours();        // Get the Cells immediately surrounding
    GameObject *getOccupant();                  // What is currently occupying Cell? (NULL if nothing is)
    void setOccupant(GameObject *GO);           // Set what is currently occupying Cell
    bool canMoveHere(GameObject *GO);           // Returns true if GO is able to move to here based on rules defined

    friend std::ostream &operator<<(std::ostream &out, Cell &cell);
};

#endif
