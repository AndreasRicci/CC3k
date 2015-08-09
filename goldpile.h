#ifndef __GOLDPILE_H__
#define __GOLDPILE_H__

#include "treasure.h"
#include "player.h"

class GoldPile : public Treasure {
public:
    GoldPile(Game * game, int value);
    ~GoldPile();
    Player * take(Player * player);
};

#endif
