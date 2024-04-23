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

    /*
    // check if bug is at the top edge of the board (y = 0)
    if (position.second == 0) {
        // check if bug is at top left corner
        if (position.first == 0) {
            if (direction == 1 || direction == 4) {
                return true;
            }
        }
            // check if bug is at top right corner
        else if (position.first == 9) {
            if (direction == 1 || direction == 2) {
                return true;
            }
        } else if (direction == 1) {
            return true;
        }
    }
        // check if bug is at bottom edge of the board (y = 9)
    else if (position.second == 9) {
        // check if bug is at bottom left corner
        if (position.first == 0) {
            if (direction == 3 || direction == 4) {
                return true;
            }
        }
            // check if bug is at bottom right corner
        else if (position.first == 9) {
            if (direction == 2 || direction == 3) {
                return true;
            }
        } else if (direction == 3) {
            return true;
        }
    }
    else if (position.first == 0 && direction == 4)
    {
        return true;
    }
    else if (position.first == 9 && direction == 2)
    {
        return true;
    }
    else
    {
        return false; // way is not blocked
    }
    return false;
     */


