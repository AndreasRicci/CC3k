#ifndef __BOOSTDEFENCE_H__
#define __BOOSTDEFENCE_H__

#include "positivepotion.h"
#include "player.h"
#include "cell.h"

class BoostDefence : public PositivePotion {
private:
    static bool taken;
public:
    ~BoostDefence();
    BoostDefence(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
