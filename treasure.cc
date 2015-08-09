#include "treasure.h"

Treasure::Treasure(int value, Game *game): Item('G', game), value(value) { }

Treasure::~Treasure() { }
