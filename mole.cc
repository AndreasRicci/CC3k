#ifdef DLC

#include "mole.h"
#include <sstream>
#include "playerclass.h"
#include "constants.h"
#include "baseplayer.h"
#include "utils.h"
#include "game.h"
#include "cell.h"
#include <ncurses.h>
#include <vector>

using namespace std;

Mole::Mole(Player * player): PlayerClass(player) {
    init_pair(3, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_CYAN);
    durability = 50;
    tunnelMode = false;
}

Mole::~Mole(){
    delete component;
}

void Mole::getSpecialBar(){
    ostringstream m;
    m << "Pickaxe: " << durability << "/50";
    game->displayBartition(durability, 50, 20, m.str(), 3, 4);
}
/*
int Mole::getAttack(){
    if (tunnelMode)
        return attack + 10;
    else
        return attack;
}
*/
bool Mole::canMoveInDirection(int dir){
    vector<Cell *> neighbours = location->getNeighbours();
    Cell *newLocation = neighbours.at(dir);
    if (newLocation->getOccupant() == NULL){
        char ch = newLocation->getAppearance();
        if (ch == '|' || ch == '-' || ch == ' '){
            if (tunnelMode){
                if(newLocation->getEdge()){
                    game->addAction("Can't exit edge!");
                    return false;
                }
                durability--;
                newLocation->setAppearance('#');
                game->addAction("Tunnelling through wall!");
                if (durability <= 0){
                    tunnelMode = false;
                    game->addAction("Your pickaxe broke!");
                    game->addAction("Tunnel Mode, OFF!");
                }
                return true;
            }
            return false;
        }
        else{
            return ch == '.' || ch == '#' || ch == '+';
        }
    }
    else{
        game->playerAttackInDirection(dir);
        return newLocation->getOccupant() == NULL;
    }
}

void Mole::specialAction(std::string action){
    if (action == ":tunnel" || action == ":t"){
        if (durability > 0){
            tunnelMode = true;
            game->addAction("Tunnel Mode, ON!");
        }
        else{
            game->addAction("Your pickaxe is broken...");
        }
    }
    else if (action == ":stop" || action == ":s"){
        if (!tunnelMode){
            game->addAction("You're not in Tunnel Mode!");
        }
        else{
            tunnelMode = false;
            game->addAction("Tunnel Mode, OFF!");
        }
    }
    else if (action == ":fix" || action == ":f"){
        if (durability < 50 && getGold() >= 5){
            setGold(getGold() - 5);
            durability = 50;
            game->addAction("Pickaxe repaired.");
        }
        else if (getGold() < 5){
            game->addAction("Insufficient gold. (Cost: 5)");
        }
        else{
            game->addAction("Your pickaxe is already in perfect condition!");
        }
    }
    else{
        game->addAction("Command unknown.");
    }
}

#endif
