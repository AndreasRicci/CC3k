#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "item.h"
#include "game.h"

class Treasure : public Item {
protected:
    int value;
    Treasure(int value, Game *game);
public:
    virtual ~Treasure() = 0;
};

#endif
