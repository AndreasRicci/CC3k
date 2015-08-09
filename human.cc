#include "human.h"
#include "game.h"
#include "constants.h"

Human::Human(Game *game):
    BasePlayer(game, 
        RACE[HUMAN][HP],
        RACE[HUMAN][ATK],
        RACE[HUMAN][DEF],
        RACE[HUMAN][ACCURACY],
        RACE[HUMAN][EVASION],
        RACE[HUMAN][GOLD_MULTIPLIER],
        RACE[HUMAN][SCORE_MULTIPLIER],
        RACE[HUMAN][POSITIVE_POTION_MULTIPLIER],
        RACE[HUMAN][NEGATIVE_POTION_MULTIPLIER]
               ) { }
