#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//create function to find number of differences
int numberOfDifferences(vector<int> joltAdapters)
{

    //initialize 1 and 3 jolt differences
    int oneJoltDiff = 0;
    int threeJoltDiff = 0;

    for (int i = 0; i < joltAdapters.size() - 1; i++)
    {

        //if difference is 1, increment oneJoltDiff
        if (joltAdapters[i + 1] - joltAdapters[i] == 1)
        {
            oneJoltDiff++;
        }

        //if difference is 3, increment threeJoltDiff
        else if (joltAdapters[i + 1] - joltAdapters[i] == 3)
        {
            threeJoltDiff++;
        }

        //if other difference is found, print
        else
        {
            cout << "Unknown Jolt Diff of: " << joltAdapters[i + 1] - joltAdapters[i] << endl;
        }
    }

    //return product of oneJoltDiff and threeJoltDiff
    return oneJoltDiff * threeJoltDiff;
}

int main()
{
    ifstream file("JoltAdapters.txt");
    string str;
    int ans;

    //create vector and push an initial 0 onto it
    vector<int> joltAdapters;
    joltAdapters.push_back(0);

    while (getline(file, str))
    {
        joltAdapters.push_back(stoi(str));
    }

    //sort jolt adapters from least to greatest
    sort(joltAdapters.begin(), joltAdapters.end());

    //push back greatest value + 3 for built in joltage adapter
    int builtInAdapter = joltAdapters[joltAdapters.size() - 1] + 3;
    joltAdapters.push_back(builtInAdapter);

    //call function to find number of differences
    ans = numberOfDifferences(joltAdapters);
    cout << "Ans is: " << ans << endl;
    return ans;
}