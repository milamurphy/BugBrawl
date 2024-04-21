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

using namespace std;
//using namespace sf;

void readFile(vector<Bug*>& bugs_vector);
void parseLine(const string& strLine, vector<Bug*>& bugs_vector);

int main() {
    vector<Bug*> bugs_vector; // pointer to Bug
    readFile(bugs_vector);
    // Create vector of 100 cells in Board.cpp, each cell contains a vector of bugs



    Board board;
    //board.displayBoard();

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

            bugs_vector.push_back(new Crawler(id, x, y, direction, size));
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

            bugs_vector.push_back(new Hopper(id, x, y, direction, size, hopLength));
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