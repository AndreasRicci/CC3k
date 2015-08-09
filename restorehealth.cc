#include "restorehealth.h"
#include "player.h"
#include "utils.h"
#include "baseplayer.h"
#include "language.h"

bool RestoreHealth::taken = false;

RestoreHealth::RestoreHealth(Game *game): PositivePotion("RH", game) { }

RestoreHealth::~RestoreHealth() {
    taken = false;
}

Player * RestoreHealth::take(Player *player){
    taken = true;
    
    // Removing from board
    location->setOccupant(NULL);
    location = NULL;
    
    // Calculate HP After
    int afterPotion = potionEffect(player->getCurrentHP(), POTIONS[RH][HP_CHANGE], player->getPositivePotionMultiplier(), player->getMaxHP());
    BasePlayer::getInstance()->setCurrentHP(afterPotion);
    
    player->notifyTookHealth();
    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("and-") + Language::getText("uses") + Language::getText(shorthand) + ".");
    return player;
}

bool RestoreHealth::hasTaken(){
    return taken;
}
