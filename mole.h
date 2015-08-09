#ifdef DLC

#ifndef __MOLE_H__
#define __MOLE_H__

#include "playerclass.h"
#include "player.h"
#include <string>
#include <ncurses.h>

class Mole : public PlayerClass {
private:
    int durability;
    bool tunnelMode;
public:
    bool canMoveInDirection(int dir);           // Yes? No?
    void getSpecialBar();                       // Gets special bar
    void specialAction(std::string action);     // Gets special action dispatcher
    Mole(Player *component);
    ~Mole();
};

#endif

#endif
