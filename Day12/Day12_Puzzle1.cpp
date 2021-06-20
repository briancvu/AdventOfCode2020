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

//function to handle movement in cardinal direction
void handleCardinalDirection(string instruction, int &north, int &south, int &east, int &west)
{
    if (instruction[0] == 'N')
    {
        north += stoi(instruction.substr(1));
    }
    else if (instruction[0] == 'S')
    {
        south += stoi(instruction.substr(1));
    }
    else if (instruction[0] == 'W')
    {
        west += stoi(instruction.substr(1));
    }
    else if (instruction[0] == 'E')
    {
        east += stoi(instruction.substr(1));
    }
    else
    {
        cerr << "Invalid Input, handleCardinalDirection" << endl;
    }
}

//function to handle forward movement
void handleForward(string instruction, string curDirection, int &north, int &south, int &east, int &west)
{
    int valToMove = stoi(instruction.substr(1));
    if (curDirection == "north")
    {
        north += valToMove;
    }
    else if (curDirection == "south")
    {
        south += valToMove;
    }
    else if (curDirection == "west")
    {
        west += valToMove;
    }
    else if (curDirection == "east")
    {
        east += valToMove;
    }
    else
    {
        cerr << "Invalid Input, handleForward" << endl;
    }
}

//function to handle turn
void handleTurn(string instruction, string &curDirection)
{

    //use iterator to find current index in directions vector
    auto it = find(directions.begin(), directions.end(), curDirection);
    int index = it - directions.begin();
    int turnRadius = stoi(instruction.substr(1));

    if (instruction[0] == 'L')
    {
        if (turnRadius == 90)
        {
            //need to use special modulo equation for negative numbers
            //as % is not modulo, but division remainder
            curDirection = directions[(((index - 1) % 4) + 4) % 4];
        }
        else if (turnRadius == 180)
        {
            curDirection = directions[(((index - 2) % 4) + 4) % 4];
        }
        else if (turnRadius == 270)
        {
            curDirection = directions[(((index - 3) % 4) + 4) % 4];
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
            curDirection = directions[(((index + 1) % 4) + 4) % 4];
        }
        else if (turnRadius == 180)
        {
            curDirection = directions[(((index + 2) % 4) + 4) % 4];
        }
        else if (turnRadius == 270)
        {
            curDirection = directions[(((index + 3) % 4) + 4) % 4];
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

int findManhattanDistance(vector<string> instructions)
{
    //create int values for the manhattan distance, north/south values, and east/west values
    int manhattanDistance = 0;
    int north = 0, south = 0, east = 0, west = 0;
    string curDirection = "east";

    //create substring and int var for distance value
    for (int i = 0; i < instructions.size(); i++)
    {

        //handle cardinal direction
        if (instructions[i][0] == 'N' || instructions[i][0] == 'S' || instructions[i][0] == 'E' || instructions[i][0] == 'W')
        {
            handleCardinalDirection(instructions[i], north, south, east, west);
        }

        //handle forward movement
        else if (instructions[i][0] == 'F')
        {
            handleForward(instructions[i], curDirection, north, south, east, west);
        }

        //handle turning
        else if (instructions[i][0] == 'L' || instructions[i][0] == 'R')
        {
            handleTurn(instructions[i], curDirection);
        }
        else
        {
            cerr << "Invalid Input, Main Function" << endl;
        }
    }

    //calculate manhattan distance by taking abs val of the diff in opposite directions
    manhattanDistance = abs(north - south) + abs(east - west);
    return manhattanDistance;
}

int main()
{

    //create ifstream for file and vector to hold contents
    ifstream file("navInstructions.txt");
    vector<string> instructions;

    //parse file
    parseFile(file, instructions);

    //find Manhattan distance
    int ans = findManhattanDistance(instructions);
    cout << "Answer is: " << ans << endl;
    return ans;
}