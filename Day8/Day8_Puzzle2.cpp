#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

//create function to test out an instruction swap
void swapInstruction(int &index, int &ans, vector<int> visited, vector<pair<string, int>> instructions)
{

    if (instructions[index].first == "jmp")
    {

        //if current instruction is jmp, switch to nop
        instructions[index].first = "nop";
    }
    else
    {

        //if current instruction is nop, switch to jmp
        instructions[index].first = "jmp";
    }

    while (index < instructions.size())
    {

        //if we have visited this row, break out of loop
        if (visited[index] == 1)
        {
            cout << "We break at index: " << index << endl;
            break;
        }

        //if instruction is acc, add value and increment by 1
        if (instructions[index].first == "acc")
        {
            ans += instructions[index].second;

            //set visited bit to true, then increment
            visited[index] = 1;
            index++;
        }
        else if (instructions[index].first == "jmp")
        {

            //set visited bit to true, then increment
            visited[index] = 1;
            index = index + instructions[index].second;
        }
        else
        {

            //set visited bit to true, then increment
            visited[index] = 1;
            index++;
        }
    }
}

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

    //print out instructions list
    // for (int i = 0; i < instructions.size(); i++)
    // {
    //     cout << instructions[i].first << " " << instructions[i].second << endl;
    // }

    //create visited array
    vector<int> visited(instructions.size(), 0);
    int i = 0;
    bool triedOnce = false;

    int newAns;
    int newIndex;

    while (1)
    {

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

            //if jmp, make copies of all parameters, and look for break in cycle
            //while switcing jmp to nop
            newAns = ans;
            newIndex = i;

            swapInstruction(newIndex, newAns, visited, instructions);

            //if index is greater than size, we have broken out of loop
            if (newIndex >= instructions.size() - 1)
            {
                ans = newAns;
                break;
            }

            //set visited bit to true, then increment
            visited[i] = 1;
            i = i + instructions[i].second;
        }
        else
        {

            //if nop, make copies of all parameters, and look for break in cycle
            //while switcing nop to jmp
            newAns = ans;
            newIndex = i;

            swapInstruction(newIndex, newAns, visited, instructions);

            //if index is greater than size, we have broken out of loop
            if (newIndex >= instructions.size() - 1)
            {
                ans = newAns;
                break;
            }

            //set visited bit to true, then increment
            visited[i] = 1;
            i++;
        }
    }

    cout << "Ans is: " << ans << endl;
    return ans;
}