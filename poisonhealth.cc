#include "poisonhealth.h"
#include "player.h"
#include "utils.h"
#include "baseplayer.h"
#include "language.h"

bool PoisonHealth::taken = false;

PoisonHealth::PoisonHealth(Game *game): NegativePotion("PH", game) { }

PoisonHealth::~PoisonHealth() {
    taken = false;
}

Player * PoisonHealth::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;

    // Calculate HP After
    int afterPotion = potionEffect(player->getCurrentHP(), POTIONS[PH][HP_CHANGE], player->getNegativePotionMultiplier(), player->getMaxHP());
    BasePlayer::getInstance()->setCurrentHP(afterPotion);
    
    player->notifyTookHealth();
    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return player;
}

bool PoisonHealth::hasTaken(){
    return taken;
}