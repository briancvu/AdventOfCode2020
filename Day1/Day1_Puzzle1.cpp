#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    ifstream file("ExpenseReport.txt");
    string str;
    int i = 0;
    unordered_map<int, int> map;
    vector<int> nums;

    // potentially unoptimized version
    // while (getline(file, str))
    // {
    //     int val = stoi(str, nullptr, 10);
    //     int toFind = 2020 - val;

    //     if (map.find(toFind) == map.end())
    //     {
    //         map.insert(make_pair(val, i));
    //     }
    //     else
    //     {
    //         int answer = val * toFind;
    //         cout << answer << endl;
    //         return answer;
    //     }
    //     i++;
    // }

    //optimized version
    while (getline(file, str))
    {
        int val = stoi(str, nullptr, 10);
        nums.push_back(val);
    }

    //map all values into hashmap
    for (int i = 0; i < nums.size(); i++)
    {
        map[nums[i]] = i;
    }

    //check if difference exists in hashmap, then return product
    for (int i = 0; i < nums.size(); i++)
    {
        int toFind = 2020 - nums[i];
        if (map.find(toFind) != map.end() && map[toFind] != i)
        {
            int ans = nums[i] * toFind;
            cout << ans << endl;
            return ans;
        }
    }
}
