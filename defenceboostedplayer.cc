#include "defenceboostedplayer.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"

DefenceBoostedPlayer::DefenceBoostedPlayer(Player * player): DecoratedPlayer(player) { }

DefenceBoostedPlayer::~DefenceBoostedPlayer(){
    if (component != BasePlayer::getInstance())
        delete component;
}

int DefenceBoostedPlayer::getDefence(){
    int afterPotion = potionEffect(component->getDefence(), POTIONS[BD][DEF_CHANGE], component->getPositivePotionMultiplier());
    return afterPotion;
}

int DefenceBoostedPlayer::getMaxHP(){
    return component->getMaxHP();
}

int DefenceBoostedPlayer::getCurrentHP(){
    return component->getCurrentHP();
}

int DefenceBoostedPlayer::getAttack(){
    return component->getAttack();
}

int DefenceBoostedPlayer::getGold(){
    return component->getGold();
}

int DefenceBoostedPlayer::getAccuracy(){
    return component->getAccuracy();
}

int DefenceBoostedPlayer::getEvasion(){
    return component->getEvasion();
}

int DefenceBoostedPlayer::getGoldMultiplier(){
    return component->getGoldMultiplier();
}

int DefenceBoostedPlayer::getPositivePotionMultiplier(){
    return component->getPositivePotionMultiplier();
}

int DefenceBoostedPlayer::getNegativePotionMultiplier(){
    return component->getNegativePotionMultiplier();
}

int DefenceBoostedPlayer::getScoreMultiplier(){
    return component->getScoreMultiplier();
}

#ifdef DLC
void DefenceBoostedPlayer::preAttack(Enemy *enemy){
    component->preAttack(enemy);
}
void DefenceBoostedPlayer::postAttack(Enemy *enemy){
    component->postAttack(enemy);
}
void DefenceBoostedPlayer::preAttacked(Enemy *enemy){
    component->preAttacked(enemy);
}
void DefenceBoostedPlayer::postAttacked(Enemy *enemy){
    component->postAttacked(enemy);
}
void DefenceBoostedPlayer::preMove(int dir){
    component->preMove(dir);
}
void DefenceBoostedPlayer::postMove(int dir){
    component->postMove(dir);
}
#endif