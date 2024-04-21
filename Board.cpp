#include "Board.h"
#include <iostream>

Board::Board(const vector<vector<Bug *>> &cells) : cells(cells) {}

/*
void Board::displayBoard() {
    for(auto &&row : cells) {
        for (int cell: row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
 */

