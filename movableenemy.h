#ifndef __MOVABLEENEMY_H__
#define __MOVABLEENEMY_H__

#include "enemy.h"

class MovableEnemy : public Enemy {
protected:
    #ifndef DLC
    MovableEnemy(int HP, int attack, int defence, int gold, char appearance, Game *game);
    #else
    MovableEnemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game);
    #endif
public:
    virtual ~MovableEnemy() = 0;
};

#endif
