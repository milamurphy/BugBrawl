#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>


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
                    cells[x][y].push_back(new Crawler(id, position, direction, size));
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
                    cells[x][y].push_back(new Hopper(id, position, direction, size, hopLength));
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
            cout << bug->getType() << " ";
            cout << "(" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << " ";
            cout << bug->getSize() << " ";

            switch (bug->getDirection()) {
                case 1: cout << "North "; break;
                case 2: cout << "East "; break;
                case 3: cout << "South "; break;
                case 4: cout << "West "; break;
                default: cout << "Unknown direction error"; break;
            }

            if (typeid(*bug) == typeid(Hopper)) {
                Hopper* hopperBug = dynamic_cast<Hopper*>(bug);
                if (hopperBug) {
                    cout << hopperBug->getHopLength() << " ";
                }
            }

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
            cout << bug->getType() << " ";
            cout << "(" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << " ";
            cout << bug->getSize() << " ";

            switch (bug->getDirection()) {
                case 1: cout << "North "; break;
                case 2: cout << "East "; break;
                case 3: cout << "South "; break;
                case 4: cout << "West "; break;
                default: cout << "Unknown direction error"; break;
            }

            if (bug->getType()=="Hopper") {
                Hopper* hopperBug = dynamic_cast<Hopper*>(bug); // turning bug object into hopper object to access getHopLength method
                if (hopperBug) {
                    cout << hopperBug->getHopLength() << " ";
                }
            }

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
    for(Bug *bug : bug_vector)
    {
            vector<Bug*> &v = cells[bug->getPosition().first][bug->getPosition().second];
            v.erase(remove(v.begin(), v.end(), bug));
            bug->move();
            cells[bug->getPosition().first][bug->getPosition().second].push_back(bug);

    }
    cout << "Board tapped" << endl;

    for (int x = 0; x < 10; ++x) { // iterate over each cell in the 10x10 board
        for (int y = 0; y < 10; ++y) {
            if (!cells[x][y].empty()) {
                Bug *biggestBug = cells[x][y][0]; // initalises the first bug as the biggest bug
                for (auto it = cells[x][y].begin() + 1; it != cells[x][y].end(); it++) {
                    Bug *currentBug = *it; // assign each bug as the current bug
                    if (currentBug->getSize() > biggestBug->getSize()) {
                        biggestBug = currentBug; // if the current bug is bigger than the biggest bug, become the biggest bug
                    }
                }
                for (auto it = cells[x][y].begin(); it != cells[x][y].end(); ++it) { // loop through again to add the sizes of all smaller bugs to the biggest bug
                    Bug *currentBug = *it;
                    if (currentBug != biggestBug) {
                        biggestBug->setSize(biggestBug->getSize() + currentBug->getSize());
                        currentBug->setAlive(false); // current bug is now dead
                        cout << "Killed " << currentBug->getId() << endl;
                    }
                }
            }
        }
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
        cells[x][y].push_back(bug);
    }

    for(int i=0; i<10; i++)
    {
            for (int j = 0; j < 10; j++)
            {
                cout << "(" << i << "," << j << "): ";
                if (cells[i][j].empty())
                {
                    cout << "empty";
                }
                else
                {
                    for(Bug* bug : cells[i][j])
                    {
                        cout << (typeid(bug) == typeid(Crawler) ? "Crawler" : "Hopper");
                        cout << " " << bug->getId() << " ";
                    }
                }
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

