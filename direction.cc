#include "direction.h"

using namespace std;

Direction::Direction(int northSouth, int eastWest) : northSouth(northSouth), eastWest(eastWest) { }

ostream &operator<<(ostream &out, const Direction &dir) {
    return out << "Direction has North/South of " << dir.northSouth << " and East/West of " << dir.eastWest << endl;
}
