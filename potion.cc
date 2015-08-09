#include <string>
#include "potion.h"

using namespace std;

Potion::Potion(string shorthand, Game *game) : Item('P', game), shorthand(shorthand) { }

Potion::~Potion() { }

bool Potion::hasTaken() {
    return false;
}

string Potion::getShorthand(){
    return shorthand;
}