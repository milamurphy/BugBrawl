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
        cout <<"Enter menu option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                board.initialiseBugBoard(fin);
                break;
            case 2:
                board.displayAllBugs();
                break;
            case 3:
                int bugId;
                cout <<"Enter bug ID to find: " ;
                cin >> bugId;
                board.findABug(bugId);
                break;
            case 8:
                cout <<"Exiting the program..." << endl;
                break;
            default:
                cout <<"Invalid input, please try again: ";
                break;
        }

    } while (choice != 8);
    fin.close();


    // Create vector of 100 cells in Board.cpp, each cell contains a vector of bugs


    return 0;
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