#include "itemfactory.h"
#include "dragonhoard.h"
#include "game.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"
#include "constants.h"
#include "utils.h"

ItemFactory::ItemFactory(Game *game) : game(game), normalPile(GoldPile(game, TREASURES[NORMAL_PILE][VALUE])),
                                                   smallHoard(GoldPile(game, TREASURES[SMALL_HOARD][VALUE])),
                                                   merchantHoard(GoldPile(game, TREASURES[MERCHANT_HOARD][VALUE])),
                                                   dragonHoard(DragonHoard(game)),
                                                   poisonHealth(PoisonHealth(game)),
                                                   restoreHealth(RestoreHealth(game)),
                                                   woundAttack(WoundAttack(game)),
                                                   boostAttack(BoostAttack(game)),
                                                   woundDefence(WoundDefence(game)),
                                                   boostDefence(BoostDefence(game)) { }

Item *ItemFactory::createItem(int size, Item *items[], const int probs[]) {
    int denom = 0; // Determine our denominator (to get percentage chance of spawn)
    for(int i = 0; i < size; ++i) {
        denom += probs[i];
    }
    
    int randomNum = randomIntInRange(1, denom);
    for(int i = 0, beginRange = 1, endRange = 0; i < size; ++i) {
        Item *item = items[i];
        endRange += probs[i];
        
        if(randomNum >= beginRange && randomNum <= endRange) {
            if(item == &normalPile) {
                return createNormalPile();
            } else if(item == &smallHoard) {
                return createSmallHoard();
            } else if(item == &dragonHoard) {
                return createDragonHoard();
            } else if(item == &poisonHealth) {
                return createPoisonHealth();
            } else if(item == &restoreHealth) {
                return createRestoreHealth();
            } else if(item == &woundAttack) {
                return createWoundAttack();
            } else if(item == &boostAttack) {
                return createBoostAttack();
            } else if(item == &woundDefence) {
                return createWoundDefence();
            } else if(item == &boostDefence) {
                return createBoostDefence();
            }
        }
        
        beginRange = endRange + 1;
    }
    
    // We should never get to this point. But if we do, the Item was not created.
    return NULL;
}

Potion *ItemFactory::createPotion() {
    static const int numPotions = 6;
    static Item *potions[numPotions] = {&poisonHealth, &restoreHealth, &woundAttack, &boostAttack, &woundDefence, &boostDefence};
    static const int probs[numPotions] = {POTIONS[PH][ITEM_SPAWN], POTIONS[RH][ITEM_SPAWN], POTIONS[WA][ITEM_SPAWN], POTIONS[BA][ITEM_SPAWN], POTIONS[WD][ITEM_SPAWN], POTIONS[BD][ITEM_SPAWN]};
    
    return dynamic_cast<Potion *>(createItem(numPotions, potions, probs));
}

Treasure *ItemFactory::createTreasure() {
    static const int numTreasures = 3;
    static Item *treasures[numTreasures] = {&normalPile, &smallHoard, &dragonHoard};
    static const int probs[numTreasures] = {TREASURES[NORMAL_PILE][ITEM_SPAWN], TREASURES[SMALL_HOARD][ITEM_SPAWN], TREASURES[DRAGON_HOARD][ITEM_SPAWN]};
    
    return dynamic_cast<Treasure *>(createItem(numTreasures, treasures, probs));
}

GoldPile *ItemFactory::createNormalPile() {
    return new GoldPile(normalPile);
}

GoldPile *ItemFactory::createSmallHoard() {
    return new GoldPile(smallHoard);
}

GoldPile *ItemFactory::createMerchantHoard() {
    return new GoldPile(merchantHoard);
}

DragonHoard *ItemFactory::createDragonHoard() {
    return new DragonHoard(dragonHoard);
}

PoisonHealth *ItemFactory::createPoisonHealth() {
    return new PoisonHealth(poisonHealth);
}

RestoreHealth *ItemFactory::createRestoreHealth() {
    return new RestoreHealth(restoreHealth);
}

WoundAttack *ItemFactory::createWoundAttack() {
    return new WoundAttack(woundAttack);
}

BoostAttack *ItemFactory::createBoostAttack() {
    return new BoostAttack(boostAttack);
}

WoundDefence *ItemFactory::createWoundDefence() {
    return new WoundDefence(woundDefence);
}

BoostDefence *ItemFactory::createBoostDefence() {
    return new BoostDefence(boostDefence);
}
