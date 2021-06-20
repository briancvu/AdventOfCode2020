#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
    ifstream file("BootCode.txt");
    string str;
    string name;
    int ans = 0;

    //create vector of instructions
    vector<pair<string, int>> instructions;

    while (getline(file, str))
    {
        string operation = "";
        string argumentString = "";

        //create operation string from up to newline char
        operation = str.substr(0, str.find(" "));

        //create argument string from newline + 1 up to end of line
        int pos = str.find(" ");
        pos = pos + 1;
        argumentString = str.substr(pos);

        //convert string of argument to string
        int argumentVal;
        int negativeBit = argumentString[0] == '-' ? -1 : 1;
        argumentVal = stoi(argumentString.substr(1));
        argumentVal = argumentVal * negativeBit;

        //push full instruction into vector
        pair<string, int> curInstruction = {operation, argumentVal};
        instructions.push_back(curInstruction);
    }
    file.close();

    //print out instructions
    // for (int i = 0; i < instructions.size(); i++)
    // {
    //     cout << instructions[i].first << " " << instructions[i].second << endl;
    // }

    //create visited array
    vector<int> visited(instructions.size(), 0);
    int i = 0;

    //loop until a cycle is reached
    while (1)
    {
        //if we have visited this row, break out of loop
        if (visited[i] == 1)
        {
            cout << "We break at index: " << i << endl;
            break;
        }

        //if instruction is acc, add value and increment by 1
        if (instructions[i].first == "acc")
        {
            ans += instructions[i].second;

            //set visited bit to true, then increment
            visited[i] = 1;
            i++;
        }
        else if (instructions[i].first == "jmp")
        {

            //set visited bit to true, then increment
            visited[i] = 1;
            i = i + instructions[i].second;
        }
        else
        {

            //set visited bit to true, then increment
            visited[i] = 1;
            i++;
        }
    }

    cout << "Ans is: " << ans << endl;
    return ans;
}