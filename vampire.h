#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include "normalenemy.h"

class Vampire : public NormalEnemy {
#ifdef DLC
protected:
    void postAttack(Player *player);
#endif
public:
    Vampire(Game *game);
};

#endif
