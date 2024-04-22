#include <SFML/Graphics.hpp>
//sf::CircleShape shape (0.f);
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Board.h"
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include <utility>
#include <list>

using namespace std;
//using namespace sf;

void readFile(vector<Bug*>& bugs_vector);
void parseLine(const string& strLine, vector<Bug*>& bugs_vector);
void printBugs(const vector<Bug*>& bugs_vector);
void displayMenu();

int main() {
    Board board;
    int choice;
    ifstream fin("bugs.txt");

    do {
        displayMenu();
        cout << "Enter menu option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                board.initialiseBugBoard(fin);
                break;
            case 2:
                board.displayAllBugs();

            case 8:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid input, please try again: ";
                break;
        }

    } while (choice != 8);
    fin.close();

    vector<Bug*> bugs_vector; // pointer to Bug
    readFile(bugs_vector);
    // Create vector of 100 cells in Board.cpp, each cell contains a vector of bugs

    printBugs(bugs_vector);


    return 0;
}

void readFile(vector<Bug*>& bugs_vector)
{
    ifstream fin("bugs.txt");
    if(fin.good()) {
        string line;

        while (getline(fin, line))
        {
            parseLine(line, bugs_vector);
        }
        fin.close();
    }
    else {
        cout << "Unable to open file, or file is empty." << endl;
    }
}

void parseLine(const string& strLine, vector<Bug*>& bugs_vector)
{
    stringstream strStream( strLine ); // turn the line of text into a stringstream for tokenizing
    const  char DELIMITER = ';';
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

            bugs_vector.push_back(new Crawler(id, position, direction, size));
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

            bugs_vector.push_back(new Hopper(id, position, direction, size, hopLength));
        }
    }
    catch (std::invalid_argument const& e)
    {
        cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const& e)
    {
        cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }
}

void printBugs(const vector<Bug*>& bugs_vector) {
    cout << "Printing Bugs:" << endl;
    for (const auto& bug : bugs_vector) {
        cout << "Bug Type: " << (typeid(*bug) == typeid(Crawler) ? "Crawler" : "Hopper") << endl;
        cout << "ID: " << bug->getId() << endl;
        cout << "Position: (" << bug->getPosition().first << ", " << bug->getPosition().second << ")" << endl;
        cout << "Direction: " << bug->getDirection() << endl;
        cout << "Size: " << bug->getSize() << endl;
        cout << endl;
    }
}

void displayMenu() {
    cout << "=========== A Bug's Life ===========" << endl;
    cout << "1. Initialise Bug Board" << endl; // load data from file
    cout << "2. Display all Bugs" << endl;
    cout << "3. Find a bug" << endl; // given an id
    cout << "4. Tap the Bug Board" << endl;
    cout << "5. Display Life History of all Bugs" << endl; // path taken
    cout << "6. Display all Cells listing their bugs" << endl;
    cout << "7. Run simulation" << endl;
    cout << "8. Exit" << endl; // write life history of all bugs to a file
}