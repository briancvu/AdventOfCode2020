#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream file("ExpenseReport.txt");
    string str;
    int i = 0;
    unordered_map<int, int> map;
    vector<int> nums;

    // unoptimized ver
    // while (getline(file, str))
    // {
    //     int val = stoi(str, nullptr, 10);
    //     nums.push_back(val);
    //     //cout << val << endl;
    // }

    // for (int i = 0; i < nums.size(); i++)
    // {
    //     map[nums[i]] = i;
    // }

    // for (int i = 0; i < nums.size(); i++)
    // {
    //     int toFind = 2020 - nums[i];
    //     for (auto it = map.begin(); it != map.end(); ++it)
    //     {
    //         for (auto secondIt = it; secondIt != map.end(); ++secondIt)
    //         {
    //             if (it->first + secondIt->first == toFind)
    //             {
    //                 int ans = it->first * secondIt->first * nums[i];
    //                 cout << ans << endl;
    //                 return ans;
    //             }
    //         }
    //     }
    // }

    //map all values into hashmap
    while (getline(file, str))
    {
        int val = stoi(str, nullptr, 10);
        nums.push_back(val);
    }

    //sort from least to greatest to use binary search
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {

        //create boundaries to find the target value
        int front = i + 1;
        int back = nums.size() - 1;
        int target = 2020 - nums[i];

        while (front < back)
        {
            int total = nums[front] + nums[back];

            //if current total is too low, move the lower value up
            if (total < target)
            {
                front++;
            }
            //if current total is too high, move the higher value down
            else if (total > target)
            {
                back--;
            }
            else
            {
                int ans = nums[front] * nums[back] * nums[i];
                cout << ans << endl;
                return ans;
            }
        }
    }
}
