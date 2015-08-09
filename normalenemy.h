#ifndef __NORMALENEMY_H__
#define __NORMALENEMY_H__

#include "movableenemy.h"

class NormalEnemy : public MovableEnemy {
protected:
    #ifndef DLC
    NormalEnemy(int HP, int attack, int defence, int gold, char appearance, Game *game);
    #else
    NormalEnemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game);
    #endif
public:
    virtual ~NormalEnemy() = 0;
};

#endif
