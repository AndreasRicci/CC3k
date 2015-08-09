#ifndef __WOUNDDEFENCE_H__
#define __WOUNDDEFENCE_H__

#include "negativepotion.h"
#include "player.h"
#include "cell.h"

class WoundDefence : public NegativePotion {
private:
    static bool taken;
public:
    ~WoundDefence();
    WoundDefence(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
