#ifndef CA2_BOARD_H
#define CA2_BOARD_H
#include <vector>
#include <fstream>
#include "Bug.h"

using namespace std;

class Board {
private:
    vector<Bug*> bug_vector;

public:
    //explicit Board(const vector<vector<Bug *>> &cells);


public:
    Board();

    // methods
    void initialiseBugBoard(ifstream& fin);
    void displayAllBugs();
    void findABug(int id);
    void tapBoard();
    void displayLifeHistory();
    //void displayBoard();
};


#endif //CA2_BOARD_H
