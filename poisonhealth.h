#ifndef __POISONHEALTH_H__
#define __POISONHEALTH_H__

#include "negativepotion.h"
#include "player.h"
#include "cell.h"

class PoisonHealth : public NegativePotion {
private:
    static bool taken;
public:
    ~PoisonHealth();
    PoisonHealth(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
