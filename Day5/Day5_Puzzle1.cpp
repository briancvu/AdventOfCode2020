#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
    ifstream file("PlaneSeats.txt");
    string str;
    int highestSeatID = 0;

    int minRow = 0;
    int maxRow = 127;
    int minCol = 0;
    int maxCol = 7;

    int rowNumber = 0;
    int seatNumber = 0;
    vector<string> planeSeats;

    //push seat numbers into vector
    while (getline(file, str))
    {
        planeSeats.push_back(str);
        //cout << str << endl;
    }

    for (int i = 0; i < planeSeats.size(); i++)
    {

        //cout << "Min Row is: " << minRow << " Max Row is: " << maxRow << endl;

        //use binary search method to determine row number
        for (int j = 0; j < 7; j++)
        {
            if (planeSeats[i][j] == 'F')
            {
                maxRow = (maxRow + (minRow - 1)) / 2;
                //cout << "Min Row is: " << minRow << " Max Row is: " << maxRow << endl;
            }
            else
            {
                minRow = (minRow + (maxRow - 1)) / 2;
                minRow += 1;
                //cout << "Min Row is: " << minRow << " Max Row is: " << maxRow << endl;
            }
        }

        //since minRow = maxRow, rowNumber can be either of them
        rowNumber = minRow;

        //use binary search method to determine seat number
        for (int k = 7; k < 10; k++)
        {
            if (planeSeats[i][k] == 'L')
            {
                maxCol = (maxCol + (minCol - 1)) / 2;
                //cout << "Min Col is: " << minCol << " Max Col is: " << maxCol << endl;
            }
            else
            {
                minCol = (minCol + (maxCol - 1)) / 2;
                minCol += 1;
                //cout << "Min Col is: " << minCol << " Max Col is: " << maxCol << endl;
            }
        }
        //since minCol = maxCol, seatNumber can be either of them
        seatNumber = minCol;

        //calculate highestSeatID using formula: multiply row by 8, then add the column
        highestSeatID = max(highestSeatID, (rowNumber * 8) + seatNumber);

        //reset mins and maxes
        minRow = 0;
        maxRow = 127;
        minCol = 0;
        maxCol = 7;
    }

    cout << highestSeatID << endl;
    return highestSeatID;
}