#include "Bug.h"
using  namespace std;


bool Bug::isWayBlocked() const {
    switch (direction) {
        case 1:
            return position.second == 0; // returns true if y == 0 which means they are at the edge of the board
        case 2:
            return position.first == 9;
        case 3:
            return position.second == 9;
        case 4:
            return position.first == 0;
        default:
            return false;
    }
}



