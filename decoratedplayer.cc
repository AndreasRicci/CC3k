#include "decoratedplayer.h"
#include "game.h"

DecoratedPlayer::DecoratedPlayer(Player *component): 
    Player(Game::instance(), 0, 0, 0, 0, 0, 0, 0, 0, 0), component(component){ }

DecoratedPlayer::~DecoratedPlayer() {}

#ifdef DLC
Player * DecoratedPlayer::undo(){
    Player * underneath = component;
    // Deleting NULL is safe
    component = NULL;
    return underneath;
}
#endif