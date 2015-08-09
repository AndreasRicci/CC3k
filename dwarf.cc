#include "dwarf.h"
#include "game.h"
#include "constants.h"

Dwarf::Dwarf(Game *game):
    BasePlayer(game, 
        RACE[DWARF][HP],
        RACE[DWARF][ATK],
        RACE[DWARF][DEF],
        RACE[DWARF][ACCURACY],
        RACE[DWARF][EVASION],
        RACE[DWARF][GOLD_MULTIPLIER],
        RACE[DWARF][SCORE_MULTIPLIER],
        RACE[DWARF][POSITIVE_POTION_MULTIPLIER],
        RACE[DWARF][NEGATIVE_POTION_MULTIPLIER]) { }
