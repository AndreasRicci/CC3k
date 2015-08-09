#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gameobject.h"
#include <string>
#include <ncurses.h>

class Enemy;
class Game;

class Player : public GameObject {
private:
    // Player Fields
    int maxHP;                                          // Maximum HP of the player
    int currentHP;                                      // Current HP of the player
    int attack;                                         // Player attack (used in battle calculations)
    int defence;                                        // Player defence (used in battle calculations)
    int accuracy;                                       // Percent chance of landing an attack
    int evasion;                                        // Percent chance of avoiding an attack
    int gold;                                           // Current amount of gold
    int goldMultiplier;                                 // Multiplier: Acquiring gold
    int positivePotionMultiplier;                       // Multiplier: Effects of positive potions
    int negativePotionMultiplier;                       // Multiplier: Effects of negative potions
    int scoreMultiplier;                                // Multiplier: End of game score
    #ifdef DLC
    int level;                                          // Current Level of player
    int EXP;                                            // Current EXP of player
    #endif
    
    
protected:
    Player(Game *game, int maxHP, int attack, int defence, int accuracy, int evasion, int goldMultiplier, int scoreMultiplier, int positivePotionMultiplier, int negativePotionMultiplier);
    #ifndef DLC
    virtual void preAttack(Enemy *enemy) { }            // Override: Event before attacking an Enemy
    virtual void postAttack(Enemy *enemy) { }           // Override: Event after attacking an Enemy
    virtual void preMove(int dir) { }                   // Override: Event after moving in direction dir
    virtual void postMove(int dir) { }                  // Override: Event before moving in direction dir
    virtual void preAttacked(Enemy *enemy) { }          // Override: Event before attacking an Enemy
    virtual void postAttacked(Enemy *enemy) { }         // Override: Event after attacking an Enemy
    #endif
public:
    virtual ~Player() = 0;
    
    virtual int getMaxHP();                             // Gets Max HP
    void setMaxHP(int HP);                              // Sets Max HP
    virtual int getCurrentHP();                         // Gets HP
    void setCurrentHP(int HP);                          // Sets HP
    virtual int getAttack();                            // Gets attack
    void setAttack(int atk);                            // Sets attack 
    virtual int getDefence();                           // Gets defence
    void setDefence(int def);                           // Sets defence
    virtual int getGold();                              // Gets gold
    void setGold(int gold);                             // Sets gold
    virtual int getAccuracy();                          // Gets accuracy
    void setAccuracy(int acc);                          // Sets accuracy
    virtual int getEvasion();                           // Gets evasion
    void setEvasion(int eva);                           // Sets evasion
    virtual int getGoldMultiplier();                    // Gets gold multiplier
    void setGoldMultiplier(int multiplier);             // Sets gold multiplier
    virtual int getPositivePotionMultiplier();          // Gets positive potion effect multiplier
    void setPositivePotionMultiplier(int multiplier);   // Sets positive potion effect multiplier
    virtual int getNegativePotionMultiplier();          // Gets negative potion effect multiplier
    void setNegativePotionMultiplier(int multiplier);   // Sets negative potion effect multiplier
    virtual int getScoreMultiplier();                   // Gets score multiplier
    void setScoreMultiplier(int multiplier);            // Sets score multiplier
    virtual void attackEnemy(Enemy *enemy);             // Attack enemy
    void notifyTookHealth();                            // Took a (potentially) bad potion!
    void notifyGotAttacked(Enemy *enemy);               // Notify the Player that it was targetted for attack
    virtual bool canMoveInDirection(int dir);           // Can this Enemy move in the given direction?
    void moveInDirection(int dir);                      // Move in specified direction (if possible)
    void die();                                         // Player death

    #ifdef DLC
    // Special Action Events
    virtual void preAttack(Enemy *enemy) { }            // Override: Event before attacking an Enemy
    virtual void postAttack(Enemy *enemy) { }           // Override: Event after attacking an Enemy
    virtual void preMove(int dir) { }                   // Override: Event after moving in direction dir
    virtual void postMove(int dir) { }                  // Override: Event before moving in direction dir
    virtual void preAttacked(Enemy *enemy) { }          // Override: Event before attacking an Enemy
    virtual void postAttacked(Enemy *enemy) { }         // Override: Event after attacking an Enemy
    virtual bool isVisible();                           // Is the Player visible?
    virtual void displaySelf(WINDOW * window);          // Display self on ncurses
    virtual void getSpecialBar();                       // Use with classes
    virtual void specialAction(std::string action);     // Use with classes
    int getLevel();                                     // Gets Level
    void setLevel(int level);                           // Sets Level
    int getEXP();                                       // Gets EXP
    void setEXP(int exp);                               // Sets EXP
    void getEXPBar();                                   // Gets EXP Bar
    void notifyIncreasedEXP(int gainedEXP);             // Notify the Player that its EXP increased
    int getEXPScoreBonus();                             // Gets the score bonus at the end of the game
    #endif
};

#endif