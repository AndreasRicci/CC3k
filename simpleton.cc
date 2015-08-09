#ifdef DLC

#include "simpleton.h"
#include "playerclass.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"
#include "game.h"
#include <ncurses.h>

Simpleton::Simpleton(Player * player): PlayerClass(player) {
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
}

Simpleton::~Simpleton(){
    delete component;
}

void Simpleton::getSpecialBar(){
    game->displayBartition(1, 1, 20, "NORMAL", 3, 4);
}

void Simpleton::specialAction(std::string action){
    game->addAction("Command unknown.");
}

#endif
