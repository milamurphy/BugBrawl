#ifndef CA2_BUG_H
#define CA2_BUG_H

#include <utility>
#include <list>
using namespace std;

class Bug
{
protected:
    char type;
    int id;
    pair<int, int> position;
    int direction{};
    int size{};
    bool alive{};
    list<pair<int,int>> path;

public:
    Bug(int id, pair<int, int> position, int direction, int size) : id(id), position(position), direction(direction), size(size) {
        this->alive = true;
        this->path.push_back(position);
    }

    // Bug(int id=0);	// parameter, with default value
    //virtual ~Bug();

    virtual void move() =0;
    virtual bool isWayBlocked() { return false; }; // to do

    // Setters
    void setId(int newId) { id = newId; }
    void setPosition(pair<int, int> newPosition) { position = newPosition; }
    void setDirection(int newDirection) { direction = newDirection; }
    void setSize(int newSize) { size = newSize; }
    void setAlive(bool newAlive) { alive = newAlive; }
    void setPath(const list<pair<int, int>>& newPath) { path = newPath; }

    // Getters
    int getId() const { return id; }
    pair<int, int> getPosition() const { return position; }
    int getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const list<pair<int, int>>& getPath() const { return path; }

};

#endif