#ifndef __POTION_H__
#define __POTION_H__

#include <string>
#include "item.h"

class Potion : public Item {
protected:
    std::string shorthand;
    Potion(std::string shorthand, Game *game);
public:
    virtual ~Potion() = 0;
    virtual bool hasTaken();
    std::string getShorthand();
};

#endif
