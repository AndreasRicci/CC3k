#ifndef __NEGATIVEPOTION_H__
#define __NEGATIVEPOTION_H__

#include <string>
#include "potion.h"
#include "game.h"
#include <string>

class NegativePotion : public Potion {
protected:
    NegativePotion(std::string shorthand, Game *game);
public:
    virtual ~NegativePotion() = 0;
};

#endif
