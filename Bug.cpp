#include "Bug.h"
using  namespace std;


bool Bug::isWayBlocked() const {
    pair<int, int> nextPos = position;
    // assumes 0,0 is at the top left of the bug board
    if (direction == 1) // north
        nextPos.second++;
    else if (direction == 2) // east
        nextPos.first++;
    else if (direction == 3) // south
        nextPos.second--;
    else if (direction == 4) // west
        nextPos.first--;

    if (nextPos.first < 0 || nextPos.first > 9 || nextPos.second < 0 || nextPos.second > 9) {
        return true;
    }

    return false;
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


