#include "phoenix.h"
#include "constants.h"

#ifndef DLC
Phoenix::Phoenix(Game *game) : NormalEnemy(ENEMIES[PHOENIX][HP], ENEMIES[PHOENIX][ATK], ENEMIES[PHOENIX][DEF],
                                           ENEMIES[PHOENIX][GOLD], DISPLAY_ENEMIES[PHOENIX], game) { }
#else
Phoenix::Phoenix(Game *game) : NormalEnemy(ENEMIES[PHOENIX][HP], ENEMIES[PHOENIX][ATK], ENEMIES[PHOENIX][DEF],
                                           ENEMIES[PHOENIX][GOLD], ENEMIES[PHOENIX][EXPER], DISPLAY_ENEMIES[PHOENIX], game) { }
#endif

