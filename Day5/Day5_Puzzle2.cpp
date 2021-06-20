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
    int minRow = 0;
    int maxRow = 127;
    int minCol = 0;
    int maxCol = 7;
    int rowNumber = 0;
    int seatNumber = 0;
    vector<string> planeSeats;
    unordered_map<int, int> seatIDs;

    int seatRepresentation[128][8] = {0};
    //push seat numbers into vector
    while (getline(file, str))
    {
        planeSeats.push_back(str);
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
        int seatID = (rowNumber * 8) + seatNumber;
        seatRepresentation[rowNumber][seatNumber] = seatID;
        seatIDs[seatID] = seatID;

        //reset mins and maxes
        minRow = 0;
        maxRow = 127;
        minCol = 0;
        maxCol = 7;
    }

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (seatRepresentation[i][j] == 0)
            {
                //generate current seatID
                cout << "Found empty seat at row " << i << " and column " << j << endl;
                int seatVal = (i * 8) + j;
                //cout << "SeatVal is:" << seatVal << endl;

                //check if seatID + 1 and seatID - 1 exists within list of seat IDs
                if ((seatIDs.find(seatVal + 1) != seatIDs.end()) && (seatIDs.find(seatVal - 1) != seatIDs.end()))
                {
                    cout << "Found it!" << endl;
                    cout << seatVal << endl;
                    return seatVal;
                }
            }
        }
    }
}