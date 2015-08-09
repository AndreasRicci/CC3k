#ifndef __WOUNDATTACK_H__
#define __WOUNDATTACK_H__

#include "negativepotion.h"
#include "player.h"
#include "cell.h"

class WoundAttack : public NegativePotion {
private:
    static bool taken;
public:
    ~WoundAttack();
    WoundAttack(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
