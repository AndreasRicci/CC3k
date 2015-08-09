#ifndef __STAIRCASE_H__
#define __STAIRCASE_H__

#include "gameobject.h"
#include "game.h"

class Game;

class Staircase : public GameObject {
public:
    Staircase(Game *game);
    void takeStairs();
};

#endif
