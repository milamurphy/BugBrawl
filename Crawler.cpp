#include "Crawler.h"
#include <cstdlib>
//#include <ctime>

Crawler::~Crawler() = default;

void Crawler::move() {
    if(isWayBlocked())
    {
        direction = rand() % 4 + 1;
    }
    else
    {
        pair<int, int> newPos = position;
        if(direction ==1) // north
        {
            newPos.second += -1;
        }
        else if(direction ==2) // east
        {
            newPos.first += 1;
        }
        else if(direction ==3) // south
        {
            newPos.second += 1;
        }
        else { // west
            newPos.first -= 1;
        }

        path.push_back(newPos);
        position = newPos;
    }
}