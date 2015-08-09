#include "movableenemy.h"

#ifndef DLC
MovableEnemy::MovableEnemy(int HP, int attack, int defence, int gold, char appearance, Game *game) :
                            Enemy(HP, attack, defence, gold, appearance, game, true, true) { }
#else
MovableEnemy::MovableEnemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game) :
                            Enemy(HP, attack, defence, gold, EXP, appearance, game, true, true) { }
#endif
MovableEnemy::~MovableEnemy() { }
