#include "goblin.h"
#include "player.h"
#include "baseplayer.h"
#include "utils.h"
#include "constants.h"
#include "game.h"

#ifndef DLC
Goblin::Goblin(Game *game) : NormalEnemy(ENEMIES[GOBLIN][HP], ENEMIES[GOBLIN][ATK], ENEMIES[GOBLIN][DEF],
                                         ENEMIES[GOBLIN][GOLD], DISPLAY_ENEMIES[GOBLIN], game) { }
#else
Goblin::Goblin(Game *game) : NormalEnemy(ENEMIES[GOBLIN][HP], ENEMIES[GOBLIN][ATK], ENEMIES[GOBLIN][DEF],
                                         ENEMIES[GOBLIN][GOLD], ENEMIES[GOBLIN][EXPER], DISPLAY_ENEMIES[GOBLIN], game) { }

void Goblin::postAttack(Player *player){
    int stolen = potionEffect(player->getGold(), -1);
    if (player->getGold() > 0){
        BasePlayer::getInstance()->setGold(stolen);
        game->addAction("The Goblin has stolen a coin!");
        gold++;
    }
}
#endif