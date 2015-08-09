#include "attackwoundedplayer.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"

AttackWoundedPlayer::AttackWoundedPlayer(Player *player): DecoratedPlayer(player) { }

AttackWoundedPlayer::~AttackWoundedPlayer(){
    if (component != BasePlayer::getInstance())
        delete component;
}

int AttackWoundedPlayer::getAttack(){
    int afterPotion = potionEffect(component->getAttack(), POTIONS[WA][ATK_CHANGE], component->getNegativePotionMultiplier());
    return afterPotion;
}

int AttackWoundedPlayer::getMaxHP(){
    return component->getMaxHP();
}

int AttackWoundedPlayer::getCurrentHP(){
    return component->getCurrentHP();
}

int AttackWoundedPlayer::getDefence(){
    return component->getDefence();
}

int AttackWoundedPlayer::getGold(){
    return component->getGold();
}

int AttackWoundedPlayer::getAccuracy(){
    return component->getAccuracy();
}

int AttackWoundedPlayer::getEvasion(){
    return component->getEvasion();
}

int AttackWoundedPlayer::getGoldMultiplier(){
    return component->getGoldMultiplier();
}

int AttackWoundedPlayer::getPositivePotionMultiplier(){
    return component->getPositivePotionMultiplier();
}

int AttackWoundedPlayer::getNegativePotionMultiplier(){
    return component->getNegativePotionMultiplier();
}

int AttackWoundedPlayer::getScoreMultiplier(){
    return component->getScoreMultiplier();
}

#ifdef DLC
void AttackWoundedPlayer::preAttack(Enemy *enemy){
    component->preAttack(enemy);
}
void AttackWoundedPlayer::postAttack(Enemy *enemy){
    component->postAttack(enemy);
}
void AttackWoundedPlayer::preAttacked(Enemy *enemy){
    component->preAttacked(enemy);
}
void AttackWoundedPlayer::postAttacked(Enemy *enemy){
    component->postAttacked(enemy);
}
void AttackWoundedPlayer::preMove(int dir){
    component->preMove(dir);
}
void AttackWoundedPlayer::postMove(int dir){
    component->postMove(dir);
}
#endif