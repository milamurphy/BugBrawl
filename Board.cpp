#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <iostream>
#include <sstream>
#include <utility>

//Board::Board(const vector<vector<Bug *>> &cells) : cells(cells) {}
Board::Board() {}

void Board::initialiseBugBoard(ifstream& fin) {
    if (fin.good()) {
        string line;
        while (getline(fin, line)) {
            stringstream strStream(line);
            const char DELIMITER = ';';
            string bug_type;
            getline(strStream, bug_type, DELIMITER);
            string strTemp; // temporary string

            try {
                if (bug_type == ("C")) {
                    // bugtype, id, x, y, direction, size)
                    getline(strStream, strTemp, DELIMITER);
                    int id = stoi(strTemp); // stoi converts string to int
                    getline(strStream, strTemp, DELIMITER);
                    int x = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int y = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int direction = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int size = stoi(strTemp);

                    pair<int, int> position = make_pair(x, y);
                    //bool isAlive = true;
                    //list<pair<int, int>> path = {};

                    bug_vector.push_back(new Crawler(id, position, direction, size));
                } else if (bug_type == ("H")) {
                    // bugtype, id, x, y, direction, size, hopLength)
                    getline(strStream, strTemp, DELIMITER);
                    int id = stoi(strTemp); // stoi converts string to int
                    getline(strStream, strTemp, DELIMITER);
                    int x = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int y = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int direction = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int size = stoi(strTemp);
                    getline(strStream, strTemp, DELIMITER);
                    int hopLength = stoi(strTemp);

                    pair<int, int> position = make_pair(x, y);
                    //bool isAlive = true;
                    //list<pair<int, int>> path = {};

                    bug_vector.push_back(new Hopper(id, position, direction, size, hopLength));
                }
            }
            catch (std::invalid_argument const &e) {
                cout << "Bad input: std::invalid_argument thrown" << '\n';
            }
            catch (std::out_of_range const &e) {
                cout << "Integer overflow: std::out_of_range thrown" << '\n';
            }
        }
        fin.close();
    } else {
        cout << "Unable to open file, or file is empty." << endl;
    }
}

void Board::displayAllBugs() {
        cout << "Displaying all Bugs:" << endl;
        for (const auto& bug : bug_vector) {
            cout << "Bug Type: " << (typeid(*bug) == typeid(Crawler) ? "Crawler" : "Hopper") << endl;
            cout << "ID: " << bug->getId() << endl;
            cout << "Position: (" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << endl;
            cout << "Direction: " << bug->getDirection() << endl;
            cout << "Size: " << bug->getSize() << endl;
            cout << "Alive: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            cout << endl;
        }
}

void Board::findABug(int id) {
    bool found = false;
    for(const auto& bug : bug_vector)
    {
        if(bug->getId() == id)
        {
            found = true;
            cout << "Bug Type: " << (typeid(*bug) == typeid(Crawler) ? "Crawler" : "Hopper") << endl;
            cout << "ID: " << bug->getId() << endl;
            cout << "Position: (" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << endl;
            cout << "Direction: " << bug->getDirection() << endl;
            cout << "Size: " << bug->getSize() << endl;
            cout << "Alive: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            cout << endl;
            break;
        }
    }
    if(!found)
    {
        cout << "Bug with ID " << id << "not found." << endl;
    }
}

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

