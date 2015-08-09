#include "defencewoundedplayer.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"

DefenceWoundedPlayer::DefenceWoundedPlayer(Player * player): DecoratedPlayer(player) { }

DefenceWoundedPlayer::~DefenceWoundedPlayer(){
    if (component != BasePlayer::getInstance())
        delete component;
}

int DefenceWoundedPlayer::getDefence(){
    int afterPotion = potionEffect(component->getDefence(), POTIONS[WD][DEF_CHANGE], component->getNegativePotionMultiplier());
    return afterPotion;
}

int DefenceWoundedPlayer::getAttack(){
    return component->getAttack();
}

int DefenceWoundedPlayer::getMaxHP(){
    return component->getMaxHP();
}

int DefenceWoundedPlayer::getCurrentHP(){
    return component->getCurrentHP();
}

int DefenceWoundedPlayer::getGold(){
    return component->getGold();
}

int DefenceWoundedPlayer::getAccuracy(){
    return component->getAccuracy();
}

int DefenceWoundedPlayer::getEvasion(){
    return component->getEvasion();
}

int DefenceWoundedPlayer::getGoldMultiplier(){
    return component->getGoldMultiplier();
}

int DefenceWoundedPlayer::getPositivePotionMultiplier(){
    return component->getPositivePotionMultiplier();
}

int DefenceWoundedPlayer::getNegativePotionMultiplier(){
    return component->getNegativePotionMultiplier();
}

int DefenceWoundedPlayer::getScoreMultiplier(){
    return component->getScoreMultiplier();
}

#ifdef DLC
void DefenceWoundedPlayer::preAttack(Enemy *enemy){
    component->preAttack(enemy);
}
void DefenceWoundedPlayer::postAttack(Enemy *enemy){
    component->postAttack(enemy);
}
void DefenceWoundedPlayer::preAttacked(Enemy *enemy){
    component->preAttacked(enemy);
}
void DefenceWoundedPlayer::postAttacked(Enemy *enemy){
    component->postAttacked(enemy);
}
void DefenceWoundedPlayer::preMove(int dir){
    component->preMove(dir);
}
void DefenceWoundedPlayer::postMove(int dir){
    component->postMove(dir);
}
#endif