#ifndef __DECORATEDPLAYER_H__
#define __DECORATEDPLAYER_H__

#include "player.h"
class Player;

class DecoratedPlayer : public Player {
protected:
    Player *component;
    DecoratedPlayer(Player *component);
public:
    virtual ~DecoratedPlayer();
    #ifdef DLC
    Player *undo();
    #endif
};

#endif
