#ifndef CA2_HOPPER_H
#define CA2_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {

public:
    Hopper(int id, pair<int, int>position, int direction, int size, int hopLength) : Bug (id, position, direction, size), hopLength(hopLength) {
        this->hopLength = hopLength;
    };

    int getHopLength() const {return hopLength; };
    void setHopLength(int newHopLength) { hopLength = newHopLength; };

    //void move() override;
    ~Hopper();

protected:
    int hopLength;
    virtual void move();
};

#endif //CA2_HOPPER_H