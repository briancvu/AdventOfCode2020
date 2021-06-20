#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//create directional vectors to parse through in function
//directional vectors for corners
vector<vector<int>> topLeftDir = {{0, 1}, {1, 1}, {1, 0}};
vector<vector<int>> topRightDir = {{0, -1}, {1, -1}, {1, 0}};
vector<vector<int>> botLeftDir = {{-1, 0}, {-1, 1}, {0, 1}};
vector<vector<int>> botRightDir = {{0, -1}, {-1, -1}, {-1, 0}};

//directional vectors for rows and columns
vector<vector<int>> topRowDir = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
vector<vector<int>> botRowDir = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}};
vector<vector<int>> leftColDir = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}};
vector<vector<int>> rightColDir = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}};

//directional vector for center of 2d vector
vector<vector<int>> allDir = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

bool swapSeats(vector<vector<char>> seats, vector<vector<char>> &seatsToChange, int row, int col)
{

    //CASES FOR 4 CORNERS
    //top left edge case
    if (row == 0 && col == 0)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < topLeftDir.size(); i++)
            {
                if (seats[row + (topLeftDir[i][0])][col + (topLeftDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else
        {
            return false;
        }
    }

    //top right edge case
    else if (row == 0 && col == seats[row].size() - 1)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < topRightDir.size(); i++)
            {
                if (seats[row + (topRightDir[i][0])][col + (topRightDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else
        {
            return false;
        }
    }

    //bottom left edge case
    else if (row == seats.size() - 1 && col == 0)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < botLeftDir.size(); i++)
            {
                if (seats[row + (botLeftDir[i][0])][col + (botLeftDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else
        {
            return false;
        }
    }

    //bottom right edge case
    else if (row == seats.size() - 1 && col == seats[row].size() - 1)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < botRightDir.size(); i++)
            {
                if (seats[row + (botRightDir[i][0])][col + (botRightDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else
        {
            return false;
        }
    }

    //CASES FOR FIRST AND LAST ROW
    //top row edge case
    else if (row == 0)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < topRowDir.size(); i++)
            {
                if (seats[row + (topRowDir[i][0])][col + (topRowDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else if (seats[row][col] == '#')
        {
            int nextSeats = 0;
            for (int i = 0; i < topRowDir.size(); i++)
            {
                if (seats[row + topRowDir[i][0]][col + topRowDir[i][1]] == '#')
                {
                    nextSeats++;
                }
                if (nextSeats >= 4)
                {
                    seatsToChange[row][col] = 'L';
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    //bottom row edge case
    else if (row == seats.size() - 1)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < botRowDir.size(); i++)
            {
                if (seats[row + (botRowDir[i][0])][col + (botRowDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else if (seats[row][col] == '#')
        {
            int nextSeats = 0;
            for (int i = 0; i < botRowDir.size(); i++)
            {
                if (seats[row + botRowDir[i][0]][col + botRowDir[i][1]] == '#')
                {
                    nextSeats++;
                }
                if (nextSeats >= 4)
                {
                    seatsToChange[row][col] = 'L';
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    //CASES FOR FIRST AND LAST COL
    //left col edge case
    else if (col == 0)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < leftColDir.size(); i++)
            {
                if (seats[row + (leftColDir[i][0])][col + (leftColDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else if (seats[row][col] == '#')
        {
            int nextSeats = 0;
            for (int i = 0; i < leftColDir.size(); i++)
            {
                if (seats[row + leftColDir[i][0]][col + leftColDir[i][1]] == '#')
                {
                    nextSeats++;
                }
                if (nextSeats >= 4)
                {
                    seatsToChange[row][col] = 'L';
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    //right col edge case
    else if (col == seats[row].size() - 1)
    {
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < rightColDir.size(); i++)
            {
                if (seats[row + (rightColDir[i][0])][col + (rightColDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else if (seats[row][col] == '#')
        {
            int nextSeats = 0;
            for (int i = 0; i < rightColDir.size(); i++)
            {
                if (seats[row + rightColDir[i][0]][col + rightColDir[i][1]] == '#')
                {
                    nextSeats++;
                }
                if (nextSeats >= 4)
                {
                    seatsToChange[row][col] = 'L';
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    //rest of normal seats
    else
    {
        //cout << "main section" << endl;
        if (seats[row][col] == 'L')
        {
            for (int i = 0; i < allDir.size(); i++)
            {
                if (seats[row + (allDir[i][0])][col + (allDir[i][1])] == '#')
                {
                    return false;
                }
            }
            seatsToChange[row][col] = '#';
            return true;
        }
        else if (seats[row][col] == '#')
        {
            int nextSeats = 0;
            for (int i = 0; i < allDir.size(); i++)
            {
                if (seats[row + (allDir[i][0])][col + (allDir[i][1])] == '#')
                {
                    nextSeats++;
                }
                if (nextSeats >= 4)
                {
                    seatsToChange[row][col] = 'L';
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    //if none of the cases pass, return false for swapping seats
    return false;
}

int main()
{
    ifstream file("SeatArrangement.txt");
    string str;
    vector<vector<char>> seats;

    //parse through file and
    while (getline(file, str))
    {
        vector<char> currentRow;
        for (int i = 0; i < str.size(); i++)
        {
            char p = str[i];
            currentRow.push_back(p);
        }
        seats.push_back(currentRow);
    }

    //create empty vector to copy to
    static const vector<vector<char>> emptyVec(seats.size(), vector<char>(seats[0].size(), '.'));
    vector<vector<char>> seatsToChange = emptyVec;

    //use counter to see how many times we change in an iteration
    bool hasChanged = false;
    int changeCounter = 1;

    while (changeCounter != 0)
    {

        //reset counter every iteration
        changeCounter = 0;
        for (int i = 0; i < seats.size(); i++)
        {
            for (int j = 0; j < seats[i].size(); j++)
            {

                //run function to see if seats need to be swapped
                hasChanged = swapSeats(seats, seatsToChange, i, j);

                //if a change is made, add to counter
                if (hasChanged == true)
                {
                    changeCounter++;
                }
            }
        }

        //iterate through seats to change 2d vector to see what should be changed
        for (int i = 0; i < seats.size(); i++)
        {
            for (int j = 0; j < seats[i].size(); j++)
            {
                if (seatsToChange[i][j] == 'L' || seatsToChange[i][j] == '#')
                {
                    seats[i][j] = seatsToChange[i][j];
                }
            }
        }

        //reset seatsToChange 2d vector
        seatsToChange = emptyVec;
    }

    //once changes have stopped, iterate through main 2d vector to count number of occupied seats
    int numOfOccupied = 0;
    for (int i = 0; i < seats.size(); i++)
    {
        for (int j = 0; j < seats[i].size(); j++)
        {
            if (seats[i][j] == '#')
            {
                numOfOccupied++;
            }
        }
    }

    cout << "Ans is: " << numOfOccupied << endl;
    return numOfOccupied;
}