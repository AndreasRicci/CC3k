#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__

#include <cstdlib>
#include "treasure.h"
#include "player.h"
#include "dragon.h"

class DragonHoard : public Treasure {
private:
    Dragon * keeper;
public:
    DragonHoard(Game * game, Dragon *keeper = NULL);
    ~DragonHoard();
    Dragon * getDragon();
    void setDragon(Dragon * dragon);
    Player * take(Player * player);
};

#endif
