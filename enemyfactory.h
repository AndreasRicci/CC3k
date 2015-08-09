#ifndef __ENEMYFACTORY_H__
#define __ENEMYFACTORY_H__

#include "enemy.h"
#include "movableenemy.h"
#include "dragon.h"
#include "merchant.h"
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"

class Game;

class EnemyFactory {
private:
    Game *game;                                                          // What Game are we creating for?
    Enemy *createEnemy(int size, Enemy *enemies[], const int probs[]);   // Creates a random enemy given probabilities
    
    // Copy the following when creating new Enemies
    Dragon D;
    Merchant M;
    Werewolf W;
    Vampire V;
    Phoenix X;
    Goblin N;
    Troll T;
public:
    EnemyFactory(Game *game);
    MovableEnemy *createMovableEnemy();               // Create a random MovableEnemy
    
    // The following create an Enemy of the specified type
    Dragon *createDragon();
    Merchant *createMerchant();
    Werewolf *createWerewolf();
    Vampire *createVampire();
    Phoenix *createPhoenix();
    Goblin *createGoblin();
    Troll *createTroll();
};

#endif
