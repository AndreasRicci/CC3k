#include "vampire.h"
#include "constants.h"
#include "utils.h"
#include "player.h"
#include "language.h"
#include "game.h"
#include <iostream>
#include <sstream>

using namespace std;

#ifndef DLC
Vampire::Vampire(Game *game) : NormalEnemy(ENEMIES[VAMPIRE][HP], ENEMIES[VAMPIRE][ATK], ENEMIES[VAMPIRE][DEF],
                                           ENEMIES[VAMPIRE][GOLD], DISPLAY_ENEMIES[VAMPIRE], game) { }
#else
Vampire::Vampire(Game *game) : NormalEnemy(ENEMIES[VAMPIRE][HP], ENEMIES[VAMPIRE][ATK], ENEMIES[VAMPIRE][DEF],
                                           ENEMIES[VAMPIRE][GOLD], ENEMIES[VAMPIRE][EXPER], DISPLAY_ENEMIES[VAMPIRE], game) { }

void Vampire::postAttack(Player *player){
    int damageAbsorbed = damage(getAttack(), player->getDefence());
    setCurrentHP(getCurrentHP() + damageAbsorbed);
    
    ostringstream damageStr;
    damageStr << damageAbsorbed;
    
    Game::instance()->addAction("V" + Language::getText("absorbs") + damageStr.str() + " " + Language::getText("HP") + ".");

}    
#endif