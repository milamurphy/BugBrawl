#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "Roamer.h"
#include "Superbug.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

using namespace sf;


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
                // bug_type, id, x, y, direction, size, (hoplength))
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
                if(bug_type == "C")
                {
                    bug_vector.push_back(new Crawler(id, position, direction, size));
                    cells[x][y].push_back(new Crawler(id, position, direction, size));
                }
                else if (bug_type == ("H")) {
                    getline(strStream, strTemp, DELIMITER);
                    int hopLength = stoi(strTemp);

                    bug_vector.push_back(new Hopper(id, position, direction, size, hopLength));
                    cells[x][y].push_back(new Hopper(id, position, direction, size, hopLength));
                }
                else if (bug_type == ("R")) {
                    bug_vector.push_back(new Roamer(id, position, direction, size));
                    cells[x][y].push_back(new Roamer(id, position, direction, size));
                }
                else if (bug_type == ("S")) {
                    bug_vector.push_back(new Superbug(id, position, direction, size));
                    cells[x][y].push_back(new Superbug(id, position, direction, size));
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
        // Reference: Derek Flood
        vector<Bug*> &v = cells[bug->getPosition().first][bug->getPosition().second];
        v.erase(remove(v.begin(), v.end(), bug));
        bug->move();
        cells[bug->getPosition().first][bug->getPosition().second].push_back(bug);
    }

    cout << "Board tapped" << endl;

    // to do, if 2 bugs are the same size when they fight, pick a bug at random
    for (int x = 0; x < 10; x++) { // iterate over each cell in the 10x10 board
        for (int y = 0; y < 10; y++) {
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
                        if(currentBug->isAlive())
                        {
                            biggestBug->setSize(biggestBug->getSize() + currentBug->getSize());
                            currentBug->setAlive(false); // current bug is now dead
                            currentBug->setEatenBy(to_string((biggestBug->getId())));

                            cout << biggestBug->getId() << " Killed " << currentBug->getId() << endl;
                        }
                    }
                }
            }
        }
    } // end of bug eating for loop

    // check for winner
    int aliveBugCount = 0;
    Bug *lastAliveBug = nullptr;
    for (const auto &bug : bug_vector) {
        if (bug->isAlive()) {
            aliveBugCount++;
            lastAliveBug = bug;
        }
    }
    if (aliveBugCount == 1 && lastAliveBug != nullptr) {
        cout << "The winner is Bug ID: " << lastAliveBug->getId() << endl;
    }
}

void Board::tapBoard(const Event& event) {
    for(Bug *bug : bug_vector)
    {
        // Reference: Derek Flood
        vector<Bug*> &v = cells[bug->getPosition().first][bug->getPosition().second];
        v.erase(remove(v.begin(), v.end(), bug));

        Superbug* superbug = dynamic_cast<Superbug*>(bug);
        if (superbug) {
            // If it is, move the Superbug with the event parameter
            superbug->move(event);
        } else {
            // If not, move the bug as usual
            bug->move();
        }

        cells[bug->getPosition().first][bug->getPosition().second].push_back(bug);
    }

    cout << "Board tapped" << endl;

    // to do, if 2 bugs are the same size when they fight, pick a bug at random
    for (int x = 0; x < 10; x++) { // iterate over each cell in the 10x10 board
        for (int y = 0; y < 10; y++) {
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
                        if(currentBug->isAlive())
                        {
                            biggestBug->setSize(biggestBug->getSize() + currentBug->getSize());
                            currentBug->setAlive(false); // current bug is now dead
                            currentBug->setEatenBy(to_string((biggestBug->getId())));

                            cout << biggestBug->getId() << " Killed " << currentBug->getId() << endl;
                        }
                    }
                }
            }
        }
    } // end of bug eating for loop

    // check for winner
    int aliveBugCount = 0;
    Bug *lastAliveBug = nullptr;
    for (const auto &bug : bug_vector) {
        if (bug->isAlive()) {
            aliveBugCount++;
            lastAliveBug = bug;
        }
    }
    if (aliveBugCount == 1 && lastAliveBug != nullptr) {
        cout << "The winner is Bug ID: " << lastAliveBug->getId() << endl;
    }
}


void Board::displayLifeHistory() {
    for(const auto& bug : bug_vector)
    {
        cout << bug->getId() << " " << bug->getType() << " Path ";
        const auto& path = bug->getPath();
        for (const auto& pos : path)
        {
            cout << "(" << pos.first << ", " << pos.second << ")";
        }
        if(bug->isAlive())
        {
            cout <<", Alive!";
        }
        else
        {
            cout << " Eaten by " << bug->getEatenBy();
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
            fout << bug->getId() << " " << bug->getType() << " Path ";
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
        //cells[x][y].push_back(bug);
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
                        if(bug->isAlive())
                        {
                            cout << bug->getType() << " ";
                            cout << " " << bug->getId() << " ";
                        }
                    }
                }
                cout << endl;
            }
    }
}

void Board::runSimulation() {
    while(countAliveBugs() > 1) {
        tapBoard();
        this_thread::sleep_for(chrono::seconds(1));
        /* Reference: https://www.softwaretestinghelp.com/cpp-sleep/#:~:text=template%3C%20class%20Clock%2C%20class%20Duration,thread%20is%20to%20be%20blocked.&text=Description%3A%20This%20function%20is%20defined%20in%20the%20header. */
    }
}

int Board::countAliveBugs() const {
    int numAliveBugs = 0;
    for (const auto& bug : bug_vector) {
        if (bug->isAlive()) {
            numAliveBugs++;
        }
    }
    return numAliveBugs;
}

void Board::displayGUI() {
    RenderWindow window(VideoMode(800, 800), "A Bug's Life");

    // variables
    int cellSize = 80;
    int bugSize = 10;
    //int bugMarginX = (cellSize - bugSize) / 2; // center bugs within cells
    //int bugMarginY = (cellSize - bugSize) / 2;
    /* Reference: https://www.sfml-dev.org/tutorials/2.6/ */
    Color lightBrown(196, 164, 132);
    Color darkBrown(156, 115, 96);
    Texture crawlerTexture;
    crawlerTexture.loadFromFile("beetle.png");
    Texture hopperTexture;
    hopperTexture.loadFromFile("mantis.png");
    Texture roamerTexture;
    roamerTexture.loadFromFile("ladybug.png");
    Texture superTexture;
    superTexture.loadFromFile("superbug.png");

    Sprite crawlerSprite(crawlerTexture);
    Sprite hopperSprite(hopperTexture);
    Sprite roamerSprite(roamerTexture);
    Sprite superSprite(superTexture);

    // making sure they fit on the cells
    crawlerSprite.setScale((float)cellSize / crawlerTexture.getSize().x, (float)cellSize / crawlerTexture.getSize().y);
    hopperSprite.setScale((float)cellSize / hopperTexture.getSize().x, (float)cellSize / hopperTexture.getSize().y);
    roamerSprite.setScale((float)cellSize / roamerTexture.getSize().x, (float)cellSize / roamerTexture.getSize().y);
    superSprite.setScale((float)cellSize / superTexture.getSize().x, (float)cellSize / superTexture.getSize().y);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                tapBoard();
            } else if (event.type == Event::KeyPressed) {
                tapBoard(event);
            }
        }

        window.clear();

        // draw cells and bugs
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                // draw cell border
                RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(i * cellSize, j * cellSize);
                if ((i + j) % 2 == 0)
                    cell.setFillColor(lightBrown);
                else
                    cell.setFillColor(darkBrown);
                window.draw(cell);

                // Draw bugs in the cell
                for (auto &bug : cells[i][j]) {
                    if (bug->isAlive()) {

                        if (bug->getType() == "Crawler") {
                            crawlerSprite.setPosition(i * cellSize, j * cellSize);
                            window.draw(crawlerSprite);
                        } else if (bug->getType() == "Hopper") {
                            hopperSprite.setPosition(i * cellSize, j * cellSize);
                            window.draw(hopperSprite);
                        }
                        else if(bug->getType() == "Roamer") {
                            roamerSprite.setPosition(i * cellSize, j * cellSize);
                            window.draw(roamerSprite);
                        }
                        else if(bug->getType() == "Superbug") {
                            superSprite.setPosition(i * cellSize, j * cellSize);
                            window.draw(superSprite);
                        }
                    }
                }
            }
        }

        // Display the window
        window.display();
    }
}