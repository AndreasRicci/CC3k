#ifndef __ITEMFACTORY_H__
#define __ITEMFACTORY_H__

#include "dragonhoard.h"
#include "goldpile.h"
#include "poisonhealth.h"
#include "restorehealth.h"
#include "woundattack.h"
#include "wounddefence.h"
#include "boostattack.h"
#include "boostdefence.h"

class Game;
class Item;
class Potion;
class Treasure;

class ItemFactory {
private:
    Game *game;                                                           // What Game are we creating for?
    Item *createItem(int size, Item *items[], const int probs[]);         // Creates a random item
    
    // Copy the following when creating new Items
    GoldPile normalPile;
    GoldPile smallHoard;
    GoldPile merchantHoard;
    DragonHoard dragonHoard;
    PoisonHealth poisonHealth;
    RestoreHealth restoreHealth;
    WoundAttack woundAttack;
    BoostAttack boostAttack;
    WoundDefence woundDefence;
    BoostDefence boostDefence;
public:
    ItemFactory(Game *game);
    Potion *createPotion();                                               // Create a random Potion
    Treasure *createTreasure();                                           // Create random Treasure

    // The following create an Item of the specified type
    GoldPile *createNormalPile();
    GoldPile *createSmallHoard();
    GoldPile *createMerchantHoard();
    DragonHoard *createDragonHoard();
    PoisonHealth *createPoisonHealth();
    RestoreHealth *createRestoreHealth();
    WoundAttack *createWoundAttack();
    BoostAttack *createBoostAttack();
    WoundDefence *createWoundDefence();
    BoostDefence *createBoostDefence();
};

#endif
