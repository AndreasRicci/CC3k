#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "gameobject.h"

class Cell;
class Player;

class Enemy : public GameObject {
protected:
    int currentHP;              // How health the Enemy currently has
    int attack;                 // Attack of the Enemy (used in battle calculations)
    int defence;                // Defence of the Enemy (used in battle calculations)
    int gold;                   // How much gold does this Enemy have? (i.e base amount player gets)
    #ifdef DLC
    int EXP;
    #endif
    bool turnTaken;             // Has this Enemy made its move? (Attacking, moving, etc.)

    #ifdef DLC
    Enemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game, bool isMovable = true, bool canAttack = true);
    #else
    Enemy(int HP, int attack, int defence, int gold, char appearance, Game *game, bool isMovable = true, bool canAttack = true);
    #endif
    
    virtual void preAttack(Player *player) { }        // Override to do something special before attacking a Player
    virtual void postAttack(Player *player) { }       // Override to do something special after attacking a Player
    virtual void preAttacked(Player *player) { }      // Override to do something special before being attacked
    virtual void postAttacked(Player *player) { }     // Override to do something special after being attacked (but not killed)
    virtual void preMove(int dir) { }                 // Override to do something special after moving in direction dir
    virtual void postMove(int dir) { }                // Override to do something special before moving in direction dir
    virtual void preDeath() { }                       // Override to do something special before death
    void die();                                       // Kill the Enemy
public:
    virtual ~Enemy() = 0;
    
    virtual int getCurrentHP();                 // Gets this Enemy's HP. Override to do something special.
    void setCurrentHP(int hp);                  // Sets HP for this Enemy
    virtual int getAttack();                    // Gets this Enemy's attack. Override to do something special.
    void setAttack(int atk);                    // Sets attack for this Enemy
    virtual int getDefence();                   // Gets this Enemy's defence. Override to do something special.
    void setDefence(int def);                   // Sets defence for this Enemy
    virtual int getGold();                      // Gets this Enemy's gold. Override to do something special.
    void setGold(int gold);                     // Sets gold for this Enemy
    void allowTurn();                           // Allows Enemy to make a move in the current round
    bool canTakeTurn();                         // Can the Enemy make a move? (i.e move, attack, etc.)
    void attackPlayer(Player *player);          // Make this Enemy attack the Player
    void notifyGotAttacked(Player *player);     // Notify the Enemy that it was the victim of an attack
    bool canMoveInDirection(int dir);           // Can this Enemy move in the given direction?
    void moveInDirection(int dir);              // Move in specified direction (if possible)
};

#endif
