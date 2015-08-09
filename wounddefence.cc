#include "wounddefence.h"
#include "defencewoundedplayer.h"
#include "language.h"

bool WoundDefence::taken = false;

WoundDefence::WoundDefence(Game *game): NegativePotion("WD", game) { }

WoundDefence::~WoundDefence() {
    taken = false;
}

Player * WoundDefence::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;

    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return new DefenceWoundedPlayer(player);
}

bool WoundDefence::hasTaken(){
    return taken;
}
