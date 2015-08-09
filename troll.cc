#include "troll.h"
#include "constants.h"

#ifndef DLC
Troll::Troll(Game *game) : NormalEnemy(ENEMIES[TROLL][HP], ENEMIES[TROLL][ATK], ENEMIES[TROLL][DEF],
                                       ENEMIES[TROLL][GOLD], DISPLAY_ENEMIES[TROLL], game) { }
#else
Troll::Troll(Game *game) : NormalEnemy(ENEMIES[TROLL][HP], ENEMIES[TROLL][ATK], ENEMIES[TROLL][DEF],
                                       ENEMIES[TROLL][GOLD], ENEMIES[TROLL][EXPER], DISPLAY_ENEMIES[TROLL], game) { }
#endif
