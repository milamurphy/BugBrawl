#ifndef CA2_BOARD_H
#define CA2_BOARD_H
#include <vector>
#include <string>
#include <list>
#include "Bug.h"

using namespace std;

class Board {
private:
    vector<vector<Bug*>> cells;

public:
    explicit Board(const vector<vector<Bug *>> &cells);

public:
    Board();
    void displayBoard();
};


#endif //CA2_BOARD_H
