#include "item.h"
#include "cell.h"

Item::Item(char appearance, Game *game) : GameObject(appearance, game) { }

Item::~Item(){ }

bool Item::getIsMovable() {
    return isMovable;
}

bool Item::getCanAttack() {
    return canAttack;
}

Player *Item::take(Player *player){
    return player;
}
