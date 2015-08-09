#ifndef __RESTOREHEALTH_H__
#define __RESTOREHEALTH_H__

#include "positivepotion.h"
#include "player.h"
#include "cell.h"

class RestoreHealth : public PositivePotion {
private:
    static bool taken;
public:
    ~RestoreHealth();
    RestoreHealth(Game *game);
    Player *take(Player *player);
    bool hasTaken();
};

#endif
