#ifdef DLC

#ifndef __PLAYERCLASS_H__
#define __PLAYERCLASS_H__

#include "player.h"
#include "baseplayer.h"
#include <ncurses.h>
#include <string>

class Player;

class PlayerClass : public BasePlayer {
protected:
    Player *component;
    WINDOW *window;
    PlayerClass(Player *component);
public:
    ~PlayerClass();
};

#endif

#endif
