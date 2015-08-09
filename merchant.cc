#include "merchant.h"
#include "constants.h"
#include "game.h"

bool Merchant::isHostile = false;

#ifndef DLC
Merchant::Merchant(Game *game) : MovableEnemy(ENEMIES[MERCHANT][HP], ENEMIES[MERCHANT][ATK], ENEMIES[MERCHANT][DEF],
                                              ENEMIES[MERCHANT][GOLD], DISPLAY_ENEMIES[MERCHANT], game) { }
#else

Merchant::Merchant(Game *game) : MovableEnemy(ENEMIES[MERCHANT][HP], ENEMIES[MERCHANT][ATK], ENEMIES[MERCHANT][DEF],
                                              ENEMIES[MERCHANT][GOLD], ENEMIES[MERCHANT][EXPER], DISPLAY_ENEMIES[MERCHANT], game) { }
#endif
Merchant::~Merchant() { }

void Merchant::preAttacked(Player *player) {
    isHostile = true;
}

void Merchant::preDeath() {
    game->notifyMerchantDied(this);
}

bool Merchant::getIsHostile() {
    return isHostile;
}

void Merchant::setIsHostile(bool isHostile) {
    Merchant::isHostile = isHostile;
}

bool Merchant::getCanAttack() {
    return getIsHostile();
}
