#include "attackboostedplayer.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"

AttackBoostedPlayer::AttackBoostedPlayer(Player * player): DecoratedPlayer(player) { }

AttackBoostedPlayer::~AttackBoostedPlayer(){
    if (component != BasePlayer::getInstance()){
        delete component;
    }
}

int AttackBoostedPlayer::getAttack(){
    int afterPotion = potionEffect(component->getAttack(), POTIONS[BA][ATK_CHANGE], component->getPositivePotionMultiplier());
    return afterPotion;
}

int AttackBoostedPlayer::getMaxHP(){
    return component->getMaxHP();
}

int AttackBoostedPlayer::getCurrentHP(){
    return component->getCurrentHP();
}

int AttackBoostedPlayer::getDefence(){
    return component->getDefence();
}

int AttackBoostedPlayer::getGold(){
    return component->getGold();
}

int AttackBoostedPlayer::getAccuracy(){
    return component->getAccuracy();
}

int AttackBoostedPlayer::getEvasion(){
    return component->getEvasion();
}

int AttackBoostedPlayer::getGoldMultiplier(){
    return component->getGoldMultiplier();
}

int AttackBoostedPlayer::getPositivePotionMultiplier(){
    return component->getPositivePotionMultiplier();
}

int AttackBoostedPlayer::getNegativePotionMultiplier(){
    return component->getNegativePotionMultiplier();
}

int AttackBoostedPlayer::getScoreMultiplier(){
    return component->getScoreMultiplier();
}

#ifdef DLC
void AttackBoostedPlayer::preAttack(Enemy *enemy){
    component->preAttack(enemy);
}
void AttackBoostedPlayer::postAttack(Enemy *enemy){
    component->postAttack(enemy);
}
void AttackBoostedPlayer::preAttacked(Enemy *enemy){
    component->preAttacked(enemy);
}
void AttackBoostedPlayer::postAttacked(Enemy *enemy){
    component->postAttacked(enemy);
}
void AttackBoostedPlayer::preMove(int dir){
    component->preMove(dir);
}
void AttackBoostedPlayer::postMove(int dir){
    component->postMove(dir);
}
#endif