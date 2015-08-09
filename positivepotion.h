#ifndef __POSITIVEPOTION_H__
#define __POSITIVEPOTION_H__

#include <string>
#include "potion.h"
#include "game.h"
#include <string>

class PositivePotion : public Potion {
protected:
    PositivePotion(std::string shorthand, Game *game);
public:
    virtual ~PositivePotion() = 0;
};

#endif
