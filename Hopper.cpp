#include "Hopper.h"
#include <cstdlib>

Hopper::~Hopper() {}

// to do, allow hopper to hop less than the hoplength if it is close to the edge of the board
void Hopper::move() {
    bool moved = false;
    for(int i = 0; i < hopLength && !moved; i++)
    {
        if(isWayBlocked())
        {
            direction = rand() % 4 + 1;
        }
        else
        {
            moved = true;
        }
    }
    if(!isWayBlocked())
    {
        pair<int, int> newPos = position;
        if(direction ==1) // north
        {
            newPos.second -= hopLength;
        }
        else if(direction ==2) // east
        {
            newPos.first += hopLength;
        }
        else if(direction ==3) // south
        {
            newPos.second += hopLength;
        }
        else { // west
            newPos.first -= hopLength;
        }

        if(moved)
        {
            path.push_back(newPos);
            position = newPos;
        }
    }
}
