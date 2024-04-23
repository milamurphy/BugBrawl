#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>


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
                cout<<"Bad input: std::invalid_argument thrown"<<'\n';
            }
            catch (std::out_of_range const &e) {
                cout<<"Integer overflow: std::out_of_range thrown"<<'\n';
            }
        }
        cout<<"Bug board successfully initialised"<<endl;
        fin.close();
    } else {
        cout<<"Unable to open file, or file is empty."<<endl;
    }
}

void Board::displayAllBugs() {
        cout<<"Displaying all Bugs:"<< endl;
        for (const auto& bug : bug_vector) {
            cout << bug->getId() << " ";
            cout << (typeid(*bug) == typeid(Crawler) ? "Crawler" : "Hopper") << " ";
            cout << "(" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << " ";
            cout << bug->getDirection() << " "; // to do: print as print north, south, east, west
            cout << bug->getSize() << " ";
            cout << (bug->isAlive() ? "Alive" : "Dead") << endl;
        }
}

void Board::findABug(int id) {
    bool found = false;
    for(const auto& bug : bug_vector)
    {
        if(bug->getId() == id)
        {
            found = true;
            cout << bug->getId() << " ";
            cout << (typeid(*bug) == typeid(Crawler) ? "Crawler" : "Hopper") << " ";
            cout << "(" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << " ";
            cout << bug->getDirection() << " "; // to do: print as print north, south, east, west
            cout << bug->getSize() << " ";
            cout << (bug->isAlive() ? "Alive" : "Dead") << endl;
            break;
        }
    }
    if(!found)
    {
        cout <<"Bug with ID " << id << "not found." << endl;
    }
}

void Board::tapBoard() {
    for(auto& bug : bug_vector)
    {
        bug->move();
    }
}

void Board::displayLifeHistory() {
    for(const auto& bug : bug_vector)
    {
        cout << bug->getId() << " " << (typeid(*bug) == typeid(Crawler) ? "Crawler Path: " : "Hopper Path: ");
        const auto& path = bug->getPath();
        for (const auto& pos : path)
        {
            cout << "(" << pos.first << ", " << pos.second << ") ";
        }
        cout << endl;
    }
    // to do, display if bug is still alive, if not display what bug it was eaten by
}

void Board::writeLifeHistoryToFile() {
    ofstream fout("lifehistory.txt");
    if(fout.good())
    {
        // same as displayLifeHistory except output to file instead of console
        for(const auto& bug : bug_vector)
        {
            fout << bug->getId() << " " << (typeid(*bug) == typeid(Crawler) ? "Crawler Path: " : "Hopper Path: ");
            const auto& path = bug->getPath();
            for (const auto& pos : path)
            {
                fout << "(" << pos.first << ", " << pos.second << ") ";
            }
            fout << endl;
        }
        fout.close();
        cout << "Bug life history has been written to file." << endl;
    }
    else
    {
        cout << "Unable to open and write to file." << endl;
    }
}

void Board::displayAllCells() {
    for(auto bug : bug_vector)
    {
        auto position = bug->getPosition();
        int x = position.first;
        int y = position.second;
        cells[x][y] = bug;
    }

    for(int i=0; i<10; i++)
    {
            for (int j = 0; j < 10; j++)
            {
                cout << "(" << i << "," << j << "): ";
                if (cells[i][j] == nullptr)
                {
                    cout << "empty";
                }
                else
                {
                        cout << (typeid(*cells[i][j]) == typeid(Crawler) ? "Crawler" : "Hopper");
                        cout << " " << cells[i][j]->getId();
                }

                if (cells[i][j] != nullptr && j < 9 && cells[i][j + 1] != nullptr)
                {
                    cout << ", ";
                }
                cout << endl;
            }
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

