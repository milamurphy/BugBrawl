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