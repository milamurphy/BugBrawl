#ifndef CA2_BOARD_H
#define CA2_BOARD_H
#include <vector>
#include <fstream>
#include "Bug.h"

using namespace std;

class Board {
private:
    vector<Bug*> bug_vector;
    vector<vector<Bug*>> cells;

public:
    //explicit Board(const vector<vector<Bug *>> &cells);


public:
    Board() : cells(10, vector<Bug*>(10, nullptr)) {};

    // methods
    void initialiseBugBoard(ifstream& fin);
    void displayAllBugs();
    void findABug(int id);
    void tapBoard();
    void displayLifeHistory();
    void writeLifeHistoryToFile();
    void displayAllCells();
    //void displayBoard();
};


#endif //CA2_BOARD_H
