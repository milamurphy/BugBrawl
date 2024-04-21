#ifndef CA2_CRAWLER_H
#define CA2_CRAWLER_H

#include "Bug.h"
#include <list>
#include <utility>

class Crawler : public Bug {

public:
    Crawler(int id, pair<int, int> position, int direction, int size) : Bug(id, position, direction, size) {
        this->alive = true;
        this->path = {this->position};
    };

    ~Crawler();

protected:
    virtual void move();
};

#endif //CA2_CRAWLER_H