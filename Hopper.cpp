#include "Hopper.h"
#include <cstdlib>

Hopper::~Hopper() {}

// to do, allow hopper to hop less than the hoplength if it is close to the edge of the board
void Hopper::move() {
    bool blocked = isWayBlocked();
    while (blocked) {
        direction = rand() % 4 + 1;
        if (!isWayBlocked()) {
            blocked = false;
        }
    }

    pair<int, int> newPos = position;
        switch(direction) {
            case 1:
                newPos.second -= hopLength;
                if(newPos.second < 0)
                {
                    newPos.second = 0;
                }
                break;
            case 2:
                newPos.first += hopLength;
                if(newPos.first > 9)
                {
                    newPos.first = 9;
                }
                break;
            case 3:
                newPos.second += hopLength;
                if(newPos.second > 9)
                {
                    newPos.second = 9;
                }
                break;
            case 4:
                newPos.first -= hopLength;
                if(newPos.first < 0)
                {
                    newPos.first = 0;
                }
                break;
        }

        path.push_back(newPos);
        position = newPos;
}

