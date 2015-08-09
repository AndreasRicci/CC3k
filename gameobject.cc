#include <vector>
#include <algorithm>
#include "gameobject.h"
#include "game.h"
#include "cell.h"

using namespace std;

GameObject::GameObject(char appearance, Game *game, bool isMovable, bool canAttack, Cell *location) :
                        appearance(appearance), game(game), isMovable(isMovable), canAttack(canAttack), location(location) { }

GameObject::~GameObject() {
    // Remove this Object from the Game
    if(location != NULL) {
        if(location->getOccupant() == this) {
            location->setOccupant(NULL);
        }
        
        location = NULL;
    }
}

char GameObject::getAppearance() {
    return appearance;
}

Cell *GameObject::getLocation() {
    return location;
}

void GameObject::setLocation(Cell *location) {
    this->location = location;
}

bool GameObject::isOneCellFrom(const GameObject &other) {
    Cell *thisLocation = this->location;
    Cell *otherLocation = other.location;
    
    if(thisLocation == NULL || otherLocation == NULL) {
        return false;
    }
    
    // An object is within one cell of another if other's cell is a neighbour of this object's cell
    vector<Cell *> neighbours = thisLocation->getNeighbours();
    return find(neighbours.begin(), neighbours.end(), otherLocation) != neighbours.end();
}

bool GameObject::getIsMovable() {
    return isMovable;
}

bool GameObject::getCanAttack() {
    return canAttack;
}
