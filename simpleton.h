#ifdef DLC

#ifndef __SIMPLETON_H__
#define __SIMPLETON_H__

#include "playerclass.h"
#include "player.h"
#include <string>
#include <ncurses.h>

class Simpleton : public PlayerClass {
public:
    void getSpecialBar();                       // Gets special bar
    void specialAction(std::string action);     // Gets special action dispatcher
    Simpleton(Player *component);
    ~Simpleton();
};

#endif

#endif
