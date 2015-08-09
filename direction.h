#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <iostream>

// Direction denotes movement from a current position in the specific direction
struct Direction {
    const int northSouth;                 // 1 denotes north one unit, -1 denotes south one unit
    const int eastWest;                   // 1 denotes east one unit, -1 denotes west one unit
    Direction(int northSouth, int eastWest);
};

std::ostream &operator<<(std::ostream &out, const Direction &dir); // Can be used for debugging purposes

const int maxDirs = 8; // We currently only support 8 directions around a given position

// Normal directions. Order: northwest, north, northeast, west, east, southwest, south, southeast
const Direction dirs[maxDirs] = {Direction(-1, -1), Direction(-1, 0), Direction(-1, 1), Direction(0, -1),
                                 Direction(0, 1), Direction(1, -1), Direction(1, 0), Direction(1, 1)};

#endif
