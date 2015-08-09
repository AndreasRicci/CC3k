#include "woundattack.h"
#include "attackwoundedplayer.h"
#include "language.h"

bool WoundAttack::taken = false;

WoundAttack::WoundAttack(Game *game): NegativePotion("WA", game) { }

WoundAttack::~WoundAttack() {
    taken = false;
}

Player * WoundAttack::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;
    
    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return new AttackWoundedPlayer(player);
}

bool WoundAttack::hasTaken(){
    return taken;
}