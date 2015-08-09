#include "orc.h"
#include "game.h"
#include "constants.h"

Orc::Orc(Game *game):
    BasePlayer(game, 
        RACE[ORC][HP],
        RACE[ORC][ATK],
        RACE[ORC][DEF],
        RACE[ORC][ACCURACY],
        RACE[ORC][EVASION],
        RACE[ORC][GOLD_MULTIPLIER],
        RACE[ORC][SCORE_MULTIPLIER],
        RACE[ORC][POSITIVE_POTION_MULTIPLIER],
        RACE[ORC][NEGATIVE_POTION_MULTIPLIER]
               ) { }

