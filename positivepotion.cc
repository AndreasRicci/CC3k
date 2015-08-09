#include <string>
#include "positivepotion.h"

using namespace std;

PositivePotion::PositivePotion(string shorthand, Game *game) : Potion(shorthand, game) { }

PositivePotion::~PositivePotion() { }
