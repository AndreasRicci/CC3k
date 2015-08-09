#include "elf.h"
#include "game.h"
#include "constants.h"

Elf::Elf(Game *game):
    BasePlayer(game, 
        RACE[ELF][HP],
        RACE[ELF][ATK],
        RACE[ELF][DEF],
        RACE[ELF][ACCURACY],
        RACE[ELF][EVASION],
        RACE[ELF][GOLD_MULTIPLIER],
        RACE[ELF][SCORE_MULTIPLIER],
        RACE[ELF][POSITIVE_POTION_MULTIPLIER],
        RACE[ELF][NEGATIVE_POTION_MULTIPLIER]
               ) { }
