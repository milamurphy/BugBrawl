#ifndef CA2_ROAMER_H
#define CA2_ROAMER_H

#include "Bug.h"
#include <list>
#include <utility>


class Roamer : public Bug {
public:
    Roamer(int id, pair<int, int> position, int direction, int size) : Bug(id, position, direction, size) {
        this->type = "Roamer";
        this->alive = true;
        this->path = {this->position};
    };

    ~Roamer();

protected:
    virtual void move();
};

#endif //CA2_ROAMER_H