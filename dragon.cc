#include "dragon.h"
#include "dragonhoard.h"
#include "constants.h"
#include "player.h"
#include "game.h"

#ifndef DLC
Dragon::Dragon(Game *game, DragonHoard *hoard) : Enemy(ENEMIES[DRAGON][HP], ENEMIES[DRAGON][ATK], ENEMIES[DRAGON][DEF],
                                                       ENEMIES[DRAGON][GOLD], DISPLAY_ENEMIES[DRAGON], game, false, true), hoard(hoard) { }
#else
Dragon::Dragon(Game *game, DragonHoard *hoard) : Enemy(ENEMIES[DRAGON][HP], ENEMIES[DRAGON][ATK], ENEMIES[DRAGON][DEF],
                                                       ENEMIES[DRAGON][GOLD], ENEMIES[DRAGON][EXPER], DISPLAY_ENEMIES[DRAGON], game, false, true), hoard(hoard) { }
#endif

Dragon::~Dragon() { }

void Dragon::preDeath() {
    if(hoard != NULL) {
        hoard->setDragon(NULL);
    }
}

DragonHoard *Dragon::getHoard() {
    return hoard;
}

void Dragon::setHoard(DragonHoard *hoard) {
    this->hoard = hoard;
}

bool Dragon::getCanAttack() {
    Player *player = game->getPlayer();
    if(hoard != NULL && player != NULL && hoard->isOneCellFrom(*player)) {
        return true;
    }
    
    return false;
}
