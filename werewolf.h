#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__

#include "normalenemy.h"

class Werewolf : public NormalEnemy {
#ifdef DLC
protected:
    static bool hasWoundedPlayer;
    static int numberInPack;
    void postAttack(Player *player);
#endif
public:
    Werewolf(Game *game);
    ~Werewolf();
};

#endif
