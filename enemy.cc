#include <vector>
#include <sstream>
#include "enemy.h"
#include "cell.h"
#include "game.h"
#include "language.h"
#include "utils.h"
#include "player.h"
#include "baseplayer.h"
#include <iostream>

using namespace std;

#ifndef DLC
Enemy::Enemy(int HP, int attack, int defence, int gold, char appearance, Game *game, bool isMovable, bool canAttack) :
            GameObject(appearance, game, isMovable, canAttack), currentHP(HP), attack(attack), defence(defence), gold(gold), turnTaken(false) { }
#else
Enemy::Enemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game, bool isMovable, bool canAttack) :
            GameObject(appearance, game, isMovable, canAttack), currentHP(HP), attack(attack), defence(defence), gold(gold), EXP(EXP), turnTaken(false) { }
#endif
Enemy::~Enemy() { }

int Enemy::getCurrentHP() {
    return currentHP;
}

void Enemy::setCurrentHP(int hp) {
    if (hp < 0)
        currentHP = 0;
    else
        currentHP = hp;
}

int Enemy::getAttack() {
    return attack;
}

void Enemy::setAttack(int atk) {
    attack = atk;
}

int Enemy::getDefence() {
    return defence;
}

void Enemy::setDefence(int def) {
    defence = def;
}

int Enemy::getGold() {
    return gold;
}

void Enemy::setGold(int gold) {
    this->gold = gold;
}

void Enemy::allowTurn() {
    turnTaken = false;
}

bool Enemy::canTakeTurn() {
    return !turnTaken;
}

void Enemy::attackPlayer(Player *player) {
    if(player == NULL) {
        return;                 // Can't attack a Player who doesn't exist!
    }
    
    // Evasion check
    if(randomIntInRange(1, 100) <= player->getEvasion()) {
        game->addAction(getAppearance() + Language::getText("attackButMiss") + Language::getText("pc") + ".");
        return;
    }
    
    preAttack(player);
    int damageDone = damage(attack, player->getDefence());
    BasePlayer::getInstance()->setCurrentHP(player->getCurrentHP() - damageDone);
    
    ostringstream damageStr;
    damageStr << damageDone;
    
    game->addAction(getAppearance() + Language::getText("deals") + damageStr.str() + Language::getText("damageTo") + Language::getText("pc") + ".");

    player->notifyGotAttacked(this);
    
    postAttack(player);
    
    turnTaken = true;
}

void Enemy::notifyGotAttacked(Player *player) {
    if(player == NULL) {
        return;                 // Can't have been attacked by a Player who doesn't exist!
    }
    
    preAttacked(player);
    
    if(currentHP <= 0) {
        // HP is non-negative
        currentHP = 0;

        // Give gold to player; add to score
        int loot = gold * player->getGoldMultiplier() / 100;
        BasePlayer::getInstance()->setGold(player->getGold() + loot);
        game->addToScore(loot * player->getScoreMultiplier()/100);
        
        ostringstream goldAmount;
        goldAmount << loot;

        game->addAction(Language::getText("pc") + Language::getText("hasSlain") + getAppearance() + "!");
        if (loot > 0){
            game->addAction(Language::getText("pc") + Language::getText("picksUp") + goldAmount.str() + " " + Language::getText("Gold") + ".");
        }
        #ifdef DLC
        BasePlayer::getInstance()->notifyIncreasedEXP(EXP);
        #endif

        
        die();
        
        return;
    }
    
    // Enemy must not be dead
    postAttacked(player);
}

void Enemy::die() {
    preDeath();
    
    game->notifyEnemyDied(this);
}

bool Enemy::canMoveInDirection(int dir) {
    vector<Cell *> neighbours = location->getNeighbours();
    return neighbours.at(dir)->canMoveHere(this);
}

void Enemy::moveInDirection(int dir) {
    vector<Cell *> neighbours = location->getNeighbours();
    Cell *newLocation = neighbours.at(dir);
    
    // Move to the new location
    location->setOccupant(NULL);
    newLocation->setOccupant(this);
    location = newLocation;
    
    turnTaken = true;
}
