#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <cstddef>              // This is need to allow use of NULL in this header

class Game;
class Cell;

class GameObject {
protected:
    char appearance;            // What does this GameObject look like in the game?
    bool isMovable;             // Can this GameObject move?
    bool canAttack;             // Can this GameObject attack?
    Game *game;                 // The Game in which this Object is used (to notify of important events, etc.)
    Cell *location;             // The Cell which contains this GameObject (NULL if no Cell contains this)
    
    GameObject(char appearance, Game *game, bool isMovable = false, bool canAttack = false, Cell *location = NULL);
public:
    virtual ~GameObject() = 0;
    
    char getAppearance();                                // Get what this looks like in the game
    Cell *getLocation();                                 // Get where this Object is located
    void setLocation(Cell *location);                    // Set where this Object is located
    bool isOneCellFrom(const GameObject &other);         // Returns true iff this object is in 1 cell distance of other
    virtual bool getIsMovable();                         // Is this object able to move?
    virtual bool getCanAttack();                         // Is this object able to attack?
};

#endif
