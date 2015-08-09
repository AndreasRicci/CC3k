#include "boostattack.h"
#include "attackboostedplayer.h"
#include "language.h"

bool BoostAttack::taken = false;

BoostAttack::BoostAttack(Game *game): PositivePotion("BA", game) { }

BoostAttack::~BoostAttack() {
    taken = false;
}

Player * BoostAttack::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;
    
    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return new AttackBoostedPlayer(player);
}

bool BoostAttack::hasTaken(){
    return taken;
}