#ifndef CA2_HOPPER_H
#define CA2_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {

public:
    Hopper(int id, pair<int, int>position, int direction, int size, int hopLength) : Bug (id, position, direction, size), hopLength(hopLength) {
        this->type = "Hopper";
        this->alive = true;
        this->path = {this->position};
    };

    int getHopLength() const {return hopLength; };
    void setHopLength(int newHopLength) { hopLength = newHopLength; };

    //void move() override;
    ~Hopper();

protected:
    int hopLength;
    void move() override;
};

#endif //CA2_HOPPER_H