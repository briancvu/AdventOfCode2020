#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const vector<string> directions = {"north", "east", "south", "west"};

//function to parse text file
void parseFile(ifstream &file, vector<string> &instructions)
{
    string str;
    while (getline(file, str))
    {
        instructions.push_back(str);
    }
    file.close();
}

//function to print out contents of a vector of strings
void printInstructions(vector<string> instructions)
{
    for (int i = 0; i < instructions.size(); i++)
    {
        cout << instructions[i] << endl;
    }
}

//function to move waypoint in cardinal direction
void handleCardinalDirection(string instruction, vector<int> &wayPoint)
{
    int valToMove = stoi(instruction.substr(1));
    if (instruction[0] == 'N')
    {
        wayPoint[1] += valToMove;
    }
    else if (instruction[0] == 'S')
    {
        wayPoint[1] -= valToMove;
    }
    else if (instruction[0] == 'W')
    {
        wayPoint[0] -= valToMove;
    }
    else if (instruction[0] == 'E')
    {
        wayPoint[0] += valToMove;
    }
    else
    {
        cerr << "Invalid Input, handleCardinalDirection" << endl;
    }
}

//function to move ship in wayPoint direction multiplied by instruction value
void handleForward(string instruction, vector<int> wayPoint, vector<int> &ship)
{
    int valToMove = stoi(instruction.substr(1));
    ship[0] += (wayPoint[0] * valToMove);
    ship[1] += (wayPoint[1] * valToMove);
}

//function to handle turn
void handleTurn(string instruction, vector<int> &wayPoint)
{

    //get turnRadius as well as original X and Y directions
    int turnRadius = stoi(instruction.substr(1));
    int originalX = wayPoint[0];
    int originalY = wayPoint[1];

    //use mathematical formulas to calculate new waypoints
    if (instruction[0] == 'L')
    {
        if (turnRadius == 90)
        {
            wayPoint[0] = -originalY;
            wayPoint[1] = originalX;
        }
        else if (turnRadius == 180)
        {
            wayPoint[0] = -originalX;
            wayPoint[1] = -originalY;
        }
        else if (turnRadius == 270)
        {
            wayPoint[0] = originalY;
            wayPoint[1] = -originalX;
        }
        else
        {
            cerr << "Invalid Input, turnRadius" << endl;
        }
    }
    else if (instruction[0] == 'R')
    {
        if (turnRadius == 90)
        {
            wayPoint[0] = originalY;
            wayPoint[1] = -originalX;
        }
        else if (turnRadius == 180)
        {
            wayPoint[0] = -originalX;
            wayPoint[1] = -originalY;
        }
        else if (turnRadius == 270)
        {
            wayPoint[0] = -originalY;
            wayPoint[1] = originalX;
        }
        else
        {
            cerr << "Invalid Input, turnRadius" << endl;
        }
    }
    else
    {
        cerr << "Invalid Input, handleTurn" << endl;
    }
}

int findManhattanDistance(vector<string> instructions, vector<int> &wayPoint, vector<int> &ship)
{
    //create int values for the manhattan distance, north/south values, and east/west values
    int manhattanDistance = 0;
    int north = 0, south = 0, east = 0, west = 0;

    //create substring and int var for distance value
    for (int i = 0; i < instructions.size(); i++)
    {
        //handle cardinal direction
        if (instructions[i][0] == 'N' || instructions[i][0] == 'S' || instructions[i][0] == 'E' || instructions[i][0] == 'W')
        {
            handleCardinalDirection(instructions[i], wayPoint);
        }

        //handle forward movement
        else if (instructions[i][0] == 'F')
        {
            handleForward(instructions[i], wayPoint, ship);
        }

        //handle turning
        else if (instructions[i][0] == 'L' || instructions[i][0] == 'R')
        {
            handleTurn(instructions[i], wayPoint);
        }
        else
        {
            cerr << "Invalid Input, Main Function" << endl;
        }
    }

    //calculate manhattan distance by taking abs val of the diff in opposite directions
    manhattanDistance = abs(ship[0]) + abs(ship[1]);
    return manhattanDistance;
}

int main()
{

    //create ifstream for file and vector to hold contents
    ifstream file("navInstructions.txt");
    vector<string> instructions;

    //create locations for waypoint and ship
    vector<int> wayPoint = {10, 1};
    vector<int> ship = {0, 0};

    //parse file
    parseFile(file, instructions);

    //find Manhattan distance
    int ans = findManhattanDistance(instructions, wayPoint, ship);
    cout << "Answer is: " << ans << endl;
    return ans;
}