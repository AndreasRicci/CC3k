#include "boostdefence.h"
#include "defenceboostedplayer.h"
#include "language.h"

bool BoostDefence::taken = false;

BoostDefence::BoostDefence(Game *game): PositivePotion("BD", game) { }

BoostDefence::~BoostDefence() {
    taken = false;
}

Player * BoostDefence::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;

    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return new DefenceBoostedPlayer(player);
}

bool BoostDefence::hasTaken(){
    return taken;
}
