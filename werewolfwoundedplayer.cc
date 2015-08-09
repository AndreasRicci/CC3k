#ifdef DLC

#include "werewolfwoundedplayer.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"
#include "game.h"

int WerewolfWoundedPlayer::bleeding = 5;

bool WerewolfWoundedPlayer::isBleeding(){
    return bleeding > 0;
}

WerewolfWoundedPlayer::WerewolfWoundedPlayer(Player * player): DecoratedPlayer(player) { }

WerewolfWoundedPlayer::~WerewolfWoundedPlayer(){
    if (component != BasePlayer::getInstance())
        delete component;
}

int WerewolfWoundedPlayer::getDefence(){
    if (isBleeding()){
        int afterPotion = potionEffect(component->getDefence(), -10);
        return afterPotion;
    }
    else{
        return component->getDefence();
    }
}

int WerewolfWoundedPlayer::getAttack(){
    if (isBleeding()){
        int afterPotion = potionEffect(component->getAttack(), -10);
        return afterPotion;
    }
    else{
        return component->getDefence();
    }
}

int WerewolfWoundedPlayer::getMaxHP(){
    return component->getMaxHP();
}

int WerewolfWoundedPlayer::getCurrentHP(){
    return component->getCurrentHP();
}

int WerewolfWoundedPlayer::getGold(){
    return component->getGold();
}

int WerewolfWoundedPlayer::getAccuracy(){
    return component->getAccuracy();
}

int WerewolfWoundedPlayer::getEvasion(){
    return component->getEvasion();
}

int WerewolfWoundedPlayer::getGoldMultiplier(){
    return component->getGoldMultiplier();
}

int WerewolfWoundedPlayer::getPositivePotionMultiplier(){
    return component->getPositivePotionMultiplier();
}

int WerewolfWoundedPlayer::getNegativePotionMultiplier(){
    return component->getNegativePotionMultiplier();
}

int WerewolfWoundedPlayer::getScoreMultiplier(){
    return component->getScoreMultiplier();
}

#ifdef DLC
void WerewolfWoundedPlayer::preAttack(Enemy *enemy){
    component->preAttack(enemy);
}
void WerewolfWoundedPlayer::postAttack(Enemy *enemy){
    component->postAttack(enemy);
}
void WerewolfWoundedPlayer::preAttacked(Enemy *enemy){
    component->preAttacked(enemy);
}
void WerewolfWoundedPlayer::postAttacked(Enemy *enemy){
    component->postAttacked(enemy);
}
void WerewolfWoundedPlayer::preMove(int dir){
    component->preMove(dir);
}
void WerewolfWoundedPlayer::postMove(int dir) {
    BasePlayer * target = BasePlayer::getInstance();
    if (isBleeding()){
        target->setCurrentHP(potionEffect(target->getCurrentHP(), -5));
        target->notifyTookHealth();
        bleeding--;
        game->addAction("The werewolf's wound is bleeding.");
        if (!isBleeding()){
            game->addAction("\nThe werewolf's wound has healed. You feel different.");
        }
    }
    else{
        int regen = potionEffect(target->getCurrentHP(), 1, 100, component->getMaxHP());
        if (target->getCurrentHP() < target->getMaxHP()){
            target->setCurrentHP(regen);
            game->addAction("\nYour werewolf powers heal you.");
        }
    }
    component->postMove(dir);
}

#endif

#endif
