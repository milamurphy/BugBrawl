#ifndef CA2_BUG_H
#define CA2_BUG_H
#include <utility>
#include <list>
using namespace std;

class Bug
{
protected:
    char type;
    int id{};
    pair<int, int> position;
    int direction{};
    int size{};
    bool alive{};
    list<pair<int,int>> path;

public:
    // Bug(int id=0);	// parameter, with default value
    virtual void move() =0;
    virtual bool isWayBlocked() =0;

    ~Bug();  // destructor
};

#endif