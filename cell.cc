#include <iostream>
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "dragon.h"

#include <iostream>

using namespace std;

Cell::Cell(char appearance) : appearance(appearance), occupant(NULL) { }

Cell::~Cell() { }

char Cell::getAppearance() {
    return occupant == NULL ? appearance : occupant->getAppearance();
}

void Cell::setAppearance(char newAppearance) {
    appearance = newAppearance;
}

vector<Cell *> Cell::getNeighbours() {
    return neighbours;
}

void Cell::addNeighbour(Cell *newNeighbour) {
    neighbours.push_back(newNeighbour);
}

GameObject *Cell::getOccupant() {
    return occupant;
}

void Cell::setOccupant(GameObject *GO) {
    occupant = GO;
}

// Update below if time to implement Visitor pattern for movement
bool Cell::canMoveHere(GameObject *GO) {
    Enemy *enemy = dynamic_cast<Enemy *>(GO);
    if(enemy != NULL) {
        for(int i = 0; i < ENEMY_NUM_ALLOWED_CELLS; ++i) {
            if(getAppearance() == ENEMY_ALLOWED_CELLS[i]) {
                return true;
            }
        }
        
        return false;
    }
    
    Player *player = dynamic_cast<Player *>(GO);
    if(player != NULL) {
        for(int i = 0; i < PLAYER_NUM_ALLOWED_CELLS; ++i) {
            if(getAppearance() == PLAYER_ALLOWED_CELLS[i]) {
                return true;
            }
        }
        
        return false;
    }
    
    // Object must not be a Player or an Enemy, so it cannot move
    return false;
}

ostream &operator<<(ostream &out, Cell &cell) {
    return out << cell.getAppearance();
}


#ifdef DLC
void Cell::setEdge(bool edge){
    isEdge = edge;
}

bool Cell::getEdge(){
    return isEdge;
}
#endif