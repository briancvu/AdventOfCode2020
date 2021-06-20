#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;

int main()
{
    ifstream file("TreesMap.txt");
    string str;
    int curCol = 0;

    int slope1Ans = 0;
    int slope2Ans = 0;
    int slope3Ans = 0;
    int slope4Ans = 0;
    int slope5Ans = 0;

    vector<string> treesMap;

    while (getline(file, str))
    {
        int i = 0;
        int lineSize = str.length();
        treesMap.push_back(str);
    }

    //slope1
    //right 1 down 1
    for (int i = 0; i < treesMap.size(); i++)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            slope1Ans++;
        }
        curCol += 1;
    }
    curCol = 0;
    cout << "Slope 1 Ans is:" << slope1Ans << endl;

    //slope2
    //right 3 down 1
    for (int i = 0; i < treesMap.size(); i++)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            slope2Ans++;
        }
        curCol += 3;
    }
    curCol = 0;
    cout << "Slope 2 Ans is:" << slope2Ans << endl;

    //slope3
    //right 5 down 1
    for (int i = 0; i < treesMap.size(); i++)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            slope3Ans++;
        }
        curCol += 5;
    }
    curCol = 0;
    cout << "Slope 3 Ans is:" << slope3Ans << endl;

    //slope4
    //right 7 down 1
    for (int i = 0; i < treesMap.size(); i++)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            slope4Ans++;
        }
        curCol += 7;
    }
    curCol = 0;
    cout << "Slope 4 Ans is:" << slope4Ans << endl;

    //slope5
    //right 1 down 2
    for (int i = 0; i < treesMap.size(); i = i + 2)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            slope5Ans++;
        }
        curCol += 1;
    }
    cout << "Slope 5 Ans is:" << slope5Ans << endl;

    int finalAns = slope1Ans * slope2Ans * slope3Ans * slope4Ans * slope5Ans;
    cout << "Final Ans is:" << finalAns << endl;
    return finalAns;
}