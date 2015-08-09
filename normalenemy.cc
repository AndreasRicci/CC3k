#include "normalenemy.h"

#ifndef DLC
NormalEnemy::NormalEnemy(int HP, int attack, int defence, int gold, char appearance, Game *game) :
                            MovableEnemy(HP, attack, defence, gold, appearance, game) { }
#else
NormalEnemy::NormalEnemy(int HP, int attack, int defence, int gold, int EXP, char appearance, Game *game) :
                            MovableEnemy(HP, attack, defence, gold, EXP, appearance, game) { }
#endif
NormalEnemy::~NormalEnemy() { }
