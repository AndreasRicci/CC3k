#ifndef __ITEM_H__
#define __ITEM_H__

#include "gameobject.h"
#include <cstddef>

class Player;

class Item : public GameObject {
protected:
    Item(char appearance, Game *game);
public:
    virtual ~Item() = 0;
    
    virtual Player *take(Player *player);
    virtual bool getIsMovable();                         // Is this object able to move?
    virtual bool getCanAttack();                         // Is this object able to attack?
};

#endif
