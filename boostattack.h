#ifndef __BOOSTATTACK_H__
#define __BOOSTATTACK_H__

#include "positivepotion.h"
#include "player.h"
#include "cell.h"

class BoostAttack : public PositivePotion {
private:
    static bool taken;
public:
    ~BoostAttack();
    BoostAttack(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
