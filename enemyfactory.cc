#include "enemyfactory.h"
#include "constants.h"
#include "utils.h"

EnemyFactory::EnemyFactory(Game *game) : game(game), D(Dragon(game)), M(Merchant(game)), W(Werewolf(game)),
                           V(Vampire(game)), X(Phoenix(game)), N(Goblin(game)), T(Troll(game)) { }

Enemy *EnemyFactory::createEnemy(int size, Enemy *enemies[], const int probs[]) {
    int denom = 0; // Determine our denominator (to get percentage chance of spawn)
    for(int i = 0; i < size; ++i) {
        denom += probs[i];
    }
    
    int randomNum = randomIntInRange(1, denom);
    for(int i = 0, beginRange = 1, endRange = 0; i < size; ++i) {
        Enemy *enemy = enemies[i];
        endRange += probs[i];
        
        if(randomNum >= beginRange && randomNum <= endRange) {
           if(enemy == &W) {
               return createWerewolf();
           } else if(enemy == &V) {
               return createVampire();
           } else if(enemy == &N) {
               return createGoblin();
           } else if(enemy == &T) {
               return createTroll();
           } else if(enemy == &X) {
               return createPhoenix();
           } else if(enemy == &M) {
               return createMerchant();
           }
        }
        
        beginRange = endRange + 1;
    }
    
    // We should never get to this point. But if we do, the Enemy was not created.
    return NULL;
}

MovableEnemy *EnemyFactory::createMovableEnemy() {
    static const int numMovableEnemies = 6;
    static Enemy *enemies[numMovableEnemies] = {&W, &V, &N, &T, &X, &M};
    static const int probs[numMovableEnemies] = {ENEMIES[WEREWOLF][ENEMY_SPAWN], ENEMIES[VAMPIRE][ENEMY_SPAWN], ENEMIES[GOBLIN][ENEMY_SPAWN], ENEMIES[TROLL][ENEMY_SPAWN], ENEMIES[PHOENIX][ENEMY_SPAWN], ENEMIES[MERCHANT][ENEMY_SPAWN]};
    
    return dynamic_cast<MovableEnemy *>(createEnemy(numMovableEnemies, enemies, probs));
}

Dragon *EnemyFactory::createDragon() {
    return new Dragon(D);
}

Merchant *EnemyFactory::createMerchant() {
    return new Merchant(M);
}

Werewolf *EnemyFactory::createWerewolf() {
    return new Werewolf(W);
}

Vampire *EnemyFactory::createVampire() {
    return new Vampire(V);
}

Phoenix *EnemyFactory::createPhoenix() {
    return new Phoenix(X);
}

Goblin *EnemyFactory::createGoblin() {
    return new Goblin(N);
}

Troll *EnemyFactory::createTroll() {
    return new Troll(T);
}
