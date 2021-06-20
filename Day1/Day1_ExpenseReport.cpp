#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream file("ExpenseReport.txt");
    string str;
    int i = 0;
    unordered_map<int, int> map;
    while (getline(file, str))
    {
        int val = stoi(str, nullptr, 10);
        int toFind = 2020 - val;

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            cout << "Enter loop" << endl;
            for (auto secondIt = it; secondIt != map.end(); ++secondIt)
            {
                if (it->first + secondIt->first == toFind)
                {
                    return it->first * secondIt->first * toFind;
                }
            }
            map.insert(make_pair(val, i));
        }
    }
    cout << "Failed" << endl;
}
