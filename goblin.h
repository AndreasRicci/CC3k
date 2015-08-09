#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "normalenemy.h"

class Goblin : public NormalEnemy {
#ifdef DLC
protected:
    void postAttack(Player *player);
#endif
public:
    Goblin(Game *game);
};

#endif
