#include <sstream>
#include "werewolf.h"
#include "constants.h"
#include "game.h"
#include "language.h"
#include "utils.h"
#include "werewolfwoundedplayer.h"

using namespace std;

#ifndef DLC

Werewolf::Werewolf(Game *game) : NormalEnemy(ENEMIES[WEREWOLF][HP], ENEMIES[WEREWOLF][ATK], ENEMIES[WEREWOLF][DEF],
                                             ENEMIES[WEREWOLF][GOLD], DISPLAY_ENEMIES[WEREWOLF], game) { }

Werewolf::~Werewolf(){ }
#else
bool Werewolf::hasWoundedPlayer = false;
int Werewolf::numberInPack = 0;

Werewolf::Werewolf(Game *game) : NormalEnemy(ENEMIES[WEREWOLF][HP], ENEMIES[WEREWOLF][ATK], ENEMIES[WEREWOLF][DEF],
                                             ENEMIES[WEREWOLF][GOLD], ENEMIES[WEREWOLF][EXPER], DISPLAY_ENEMIES[WEREWOLF], game) {
    numberInPack++;
}

Werewolf::~Werewolf(){
    numberInPack--;
    if (numberInPack == 0)
        hasWoundedPlayer = false;
}

void Werewolf::postAttack(Player *player){
    // Would a hypothetical WerewolfWoundedPlayer bleed?
    if (!hasWoundedPlayer){
        // Dodge the werewolf's claws
        int chance = randomIntInRange(1, 100);
        
        if(chance <= player->getEvasion() * 2) {
            ostringstream chanceStr;
            chanceStr << chance;
            
            game->addAction(Language::getText("pc") + " is wounded." + chanceStr.str());
            game->updatePlayer(new WerewolfWoundedPlayer(player));
            hasWoundedPlayer = true;
        }
    }
}

#endif