#include <vector>
#include <sstream>
#include <ncurses.h>
#include "player.h"
#include "baseplayer.h"
#include "cell.h"
#include "game.h"
#include "language.h"
#include "utils.h"
#include "enemy.h"
#include "potion.h"
#include "dragonhoard.h"
#include "goldpile.h"

using namespace std;

#ifdef DLC
Player::Player(Game * game, int maxHP, int attack, int defence, int accuracy, int evasion, int goldMultiplier, int scoreMultiplier, int positivePotionMultiplier, int negativePotionMultiplier):
    GameObject('@', game, true, true), maxHP(maxHP), currentHP(maxHP), attack(attack), defence(defence), accuracy(accuracy), evasion(evasion), goldMultiplier(goldMultiplier), scoreMultiplier(scoreMultiplier), positivePotionMultiplier(positivePotionMultiplier), negativePotionMultiplier(negativePotionMultiplier), gold(0), level(0), EXP(0) { }
#endif 

#ifndef DLC
Player::Player(Game * game, int maxHP, int attack, int defence, int accuracy, int evasion, int goldMultiplier, int scoreMultiplier, int positivePotionMultiplier, int negativePotionMultiplier):
GameObject('@', game, true, true), maxHP(maxHP), currentHP(maxHP), attack(attack), defence(defence), accuracy(accuracy), evasion(evasion), goldMultiplier(goldMultiplier), scoreMultiplier(scoreMultiplier), positivePotionMultiplier(positivePotionMultiplier), negativePotionMultiplier(negativePotionMultiplier), gold(0) { }
#endif

Player::~Player() { }

void Player::die(){
    // Handled by game
    game->notifyPlayerDied();
}

int Player::getMaxHP() {
    return maxHP;
}

void Player::setMaxHP(int HP) {
    maxHP = HP;
}

int Player::getCurrentHP() {
    return currentHP;
}

void Player::setCurrentHP(int HP) {
    // HP is non-negative
    if (HP < 0)
        currentHP = 0;
    else
        currentHP = HP;
}

int Player::getAttack() {
    return attack;
}

void Player::setAttack(int atk) {
    attack = atk;
}

int Player::getDefence() {
    return defence;
}

void Player::setDefence(int def) {
    defence = def;
}

int Player::getAccuracy() {
    return accuracy;
}

void Player::setAccuracy(int acc) {
    accuracy = acc;
}

int Player::getEvasion() {
    return evasion;
}

void Player::setEvasion(int eva) {
    evasion = eva;
}

int Player::getGold() {
    return gold;
}

void Player::setGold(int gold) {
    this->gold = gold;
}

int Player::getGoldMultiplier(){
    return goldMultiplier;
}

void Player::setGoldMultiplier(int multiplier){
    goldMultiplier = multiplier;
}

int Player::getPositivePotionMultiplier(){
    return positivePotionMultiplier;
}

void Player::setPositivePotionMultiplier(int multiplier){
    positivePotionMultiplier = multiplier;
}

int Player::getNegativePotionMultiplier(){
    return negativePotionMultiplier;
}

void Player::setNegativePotionMultiplier(int multiplier){
    negativePotionMultiplier = multiplier;
}

int Player::getScoreMultiplier(){
    return scoreMultiplier;
}

void Player::setScoreMultiplier(int multiplier){
    scoreMultiplier = multiplier;
}

void Player::attackEnemy(Enemy *enemy){
    // Check: Existence of target
    if(!enemy) return;
    
    // Accuracy check
    if(randomIntInRange(1, 100) > getAccuracy()) {
        game->addAction(Language::getText("pc") + Language::getText("attackButMiss") + enemy->getAppearance());
        return;
    }
    
    preAttack(enemy);
    
    // Damage Calculation
    int damageDone = damage(getAttack(), enemy->getDefence());
    enemy->setCurrentHP(enemy->getCurrentHP() - damageDone);
    
    ostringstream damageStr;
    damageStr << damageDone;
    ostringstream hpLeft;
    hpLeft << enemy->getCurrentHP();

    game->addAction(Language::getText("pc") + Language::getText("deals") + damageStr.str() + Language::getText("damageTo") + enemy->getAppearance() + " (" + hpLeft.str() + " HP).");
    
    enemy->notifyGotAttacked(this);
    
    postAttack(enemy);
}

void Player::notifyGotAttacked(Enemy *enemy){
    // Check: Existence of attacker
    if(!enemy) return;
    
    preAttacked(enemy);
    
    // End of game 
    if(getCurrentHP() <= 0) {
        die();
        return;
    }
    
    postAttacked(enemy);
}

void Player::notifyTookHealth(){
    // End of game
    if(getCurrentHP() <= 0) {
        die();
        return;
    }
}

bool Player::canMoveInDirection(int dir){
    vector<Cell *> neighbours = location->getNeighbours();
    return neighbours.at(dir)->canMoveHere(this);
}

void Player::moveInDirection(int dir){

    preMove(dir);

    vector<Cell *> neighbours = location->getNeighbours();
    Cell *newLocation = neighbours.at(dir);
    
    // Move to the new location
    location->setOccupant(NULL);
    newLocation->setOccupant(this);
    location = newLocation;

    // Write message
    string message = "";
    message += Language::getText("pc") + Language::getText("moves") + Language::getText(DIRECTION[dir]);

    // Check location for points of interest
    int potions = 0;
    int knownPotions = 0;
    int amountPotions[TOTAL_POTIONS] = {0};
    int hoards = 0;
    int piles = 0;

    vector<Cell *> newNeighbours = newLocation->getNeighbours();
    for(vector<Cell *>::iterator i = newNeighbours.begin(); i != newNeighbours.end(); ++i) {
        Cell *cell = *i;

        // Sees a potion
        if(Potion *p = dynamic_cast<Potion *>(cell->getOccupant())) {
            potions++;
            if (p->hasTaken()){
                knownPotions++;
                amountPotions[potionToInt(p->getShorthand())]++;
            }
        }
        // Sees a dragon's hoard
        else if (DragonHoard *d = dynamic_cast<DragonHoard *>(cell->getOccupant())) {
            hoards++;
        }
        // Sees a pile of gold
        else if (GoldPile *g = dynamic_cast<GoldPile *>(cell->getOccupant())) {
            piles++;
        }
    }

    // Beginning extension of action sentence
    ostringstream amount[3];

    if (potions + hoards + piles > 0){
        message += " " + Language::getText("and-") + Language::getText("sees");
    }

    // Pluralization of Potions
    if (potions > 0){
        amount[0] << potions;

        if (potions > 1){
            if (knownPotions > 0)
                message += amount[0].str() + " " + Language::getText("potions");
            else if (knownPotions == 0)
                message += amount[0].str() + " " + Language::getText("unknownPs");
        }
        else{
            if (knownPotions == 0)
                message += "an " + Language::getText("unknownP");
            else
                message += "a " + Language::getText("potion");
        }
    }

    // Pluralization of Hoards
    if (hoards > 0){
        amount[1] << hoards;

        if (potions > 0){
            message += "," + Language::getText("and");
        }

        if (hoards > 1){
            message += amount[1].str() + " " + Language::getText("dragonHoards");
        }
        else{
            message += "a " + Language::getText("dragonHoard");
        }
    }

    // Pluralization of Piles
    if (piles > 0){
        amount[2] << piles;

        if (hoards + potions > 0){
            message += "," + Language::getText("and");
        }

        if (piles > 1){
            message += amount[2].str() + " " + Language::getText("goldPiles");
        }
        else{
            message += "a " + Language::getText("goldPile");
        }
    }

    message += ".";
    // End of message. Add first action.
    game->addAction(message);

    // Identified potions
    ostringstream potionList;
    if (knownPotions > 0){
        // The leftovers will be the unknowns
        potions -= knownPotions;

        potionList << "\nKnown Potions: ";
        for (int i = 0; i < TOTAL_POTIONS; i++){
            if (amountPotions[i] > 0){
                if (amountPotions[i] == 1)
                    potionList << "a ";
                else
                    potionList << amountPotions[i] << " ";

                potionList << Language::getText(POTIONS_SHORT[i]);

                if (amountPotions[i] > 1)
                    potionList << "s";

                knownPotions -= amountPotions[i];
                if (knownPotions > 0)
                    potionList << ", and ";
            }
        }
        potionList << ".";

        if (potions > 0)
            potionList << " (" << potions << " unknown)\n";

        game->addAction(potionList.str());
    }

    postMove(dir);
}   
#ifdef DLC
bool Player::isVisible(){
    return true;
}

void Player::displaySelf(WINDOW * window){
    waddch(window, '@' | A_STANDOUT);
}

int Player::getLevel(){
    return level;
}
void Player::setLevel(int level){
    this->level = level;
}
int Player::getEXP(){
    return EXP;
}
void Player::setEXP(int exp){
    this->EXP = exp;
}
void Player::notifyIncreasedEXP(int gainedEXP){
    BasePlayer * base = BasePlayer::getInstance();
    // Check: Max Level?
    if (base->getLevel() == 10)
        return;

    // Gain EXP
    base->setEXP(getEXP() + gainedEXP);
    ostringstream message;
    message << "\nGained " << gainedEXP << " EXP!" << endl;
    // Level Up!
    if (base->getEXP() > LEVEL_EXP_TO_NEXT[base->getLevel()]){
        // Reset Level/EXP meter
        base->setEXP(base->getEXP() - LEVEL_EXP_TO_NEXT[base->getLevel()]);
        message << "Level Up! (" << base->getLevel() << " -> " << base->getLevel() + 1 << ")" << endl;
        base->setLevel(base->getLevel()+1);
        base->setAttack(base->getAttack() + LEVEL_STATS_GAIN[base->getLevel()]);
        base->setDefence(base->getDefence() + LEVEL_STATS_GAIN[base->getLevel()]);
        base->setMaxHP(base->getMaxHP() + LEVEL_MAXHP_GAIN[base->getLevel()]);
        base->setCurrentHP(base->getMaxHP());
        message << "Stats: + " << LEVEL_STATS_GAIN[base->getLevel()] << " Atk/Def, " << LEVEL_MAXHP_GAIN[base->getLevel()] << " MaxHP." << endl;
    }
    game->addAction(message.str());
}
int Player::getEXPScoreBonus(){
    BasePlayer * base = BasePlayer::getInstance();
    int bonus = base->getEXP();
    for (int i = 0; i < base->getLevel(); i++){
        bonus += LEVEL_EXP_TO_NEXT[base->getLevel()];
        bonus += i * 100;
    }
    if (base->getLevel() == 10){
        bonus *= 2;
    }
    return bonus;
}

void Player::getEXPBar(){
    BasePlayer * base = BasePlayer::getInstance();
    ostringstream message;
    if (base->getLevel() < 10){
        message << "EXP: " << base->getEXP() << "/" << LEVEL_EXP_TO_NEXT[base->getLevel()];
        game->displayBartition(base->getEXP(), LEVEL_EXP_TO_NEXT[base->getLevel()], 20, message.str(), 5, 6, true);
    }
    else{
        message << "EXP: " << base->getEXP();
        game->displayBartition(1, 1, 20, message.str(), 5, 6, true);
    }
}

void Player::getSpecialBar(){

}

void Player::specialAction(string action){
    game->addAction("Command unknown.");
}
#endif