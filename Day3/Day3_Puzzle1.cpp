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
    int lineSize = 31;
    int ans = 0;

    vector<string> treesMap;

    while (getline(file, str))
    {
        int i = 0;
        int lineSize = str.length();
        treesMap.push_back(str);
    }

    //check if there is a "#" at the current position then shift position up 3 columns
    //use mod 31 to loop back to beginning of row as necessary
    for (int i = 0; i < treesMap.size(); i++)
    {
        if (treesMap[i][curCol % 31] == '#')
        {
            ans++;
        }
        curCol += 3;
    }
    cout << ans << endl;
    return ans;
}