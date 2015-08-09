#include "chamber.h"
#include <iostream>

using namespace std;

Cell *Chamber::getNthCell(int n) {
    return cells.at(n);
}

void Chamber::addCell(Cell *cell) {
    cells.push_back(cell);
}

int Chamber::chamberSize() {
    return (int)cells.size();
}
