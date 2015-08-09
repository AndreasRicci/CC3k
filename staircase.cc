#include "staircase.h"
#include "game.h"
#include "player.h"
#include "decoratedplayer.h"
#include "baseplayer.h"

Staircase::Staircase(Game *game): GameObject(DISPLAY_STAIRS, game) {};

void Staircase::takeStairs(){
    // "Leave behind buffs and debuffs...""
    // Check: Is the current player a decoration? Or the original?
    if (BasePlayer::getInstance() != Game::instance()->getPlayer()){
        Player * player = Game::instance()->getPlayer();
        delete player;
    }

    Game::instance()->notifyStairUse();
}