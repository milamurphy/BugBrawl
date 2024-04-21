#include "Crawler.h"
//#include <cstdlib>
//#include <ctime>

/*
Crawler::Crawler(int id, pair<int, int>position, int direction, int size, bool alive, list<pair<int, int>> path) : Bug('C', id, position, direction, size, alive) {
this->type = 'C';
this->id = id;
this->position = position;
this->direction = direction;
this->size = size;
this->alive = alive;
this->path = path;
}
 */

Crawler::~Crawler() = default;

void Crawler::move() {
    pair<int, int> newPos = position;
    if(direction ==1) // north
    {
        newPos.second += 1;
    }
    else if(direction ==2) // east
    {
        newPos.first += 1;
    }
    else if(direction ==3) // south
    {
        newPos.second -= 1;
    }
    else { // west
        newPos.first -= 1;
    }

    path.push_back(newPos);
    position = newPos;
}

// move to bug
/*
bool Crawler::isWayBlocked() {
    // assumes 0,0 is at the top left of the bug board
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
}
 */
