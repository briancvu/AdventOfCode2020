#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream file("JoltAdapters.txt");
    string str;
    long long ans = 1;
    vector<int> joltAdapters;

    int oneJoltDiff = 0;
    int threeJoltDiff = 0;

    joltAdapters.push_back(0);

    while (getline(file, str))
    {
        joltAdapters.push_back(stoi(str));
    }

    //sort jolt adapters from least to greatest
    sort(joltAdapters.begin(), joltAdapters.end());
    int builtInAdapter = joltAdapters[joltAdapters.size() - 1] + 3;
    joltAdapters.push_back(builtInAdapter);

    //create a dp vector
    vector<long long> path(joltAdapters.size(), 0);
    path[path.size() - 1] = 1;

    //start at the end of the vector (build in Adapter)
    for (int i = path.size() - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < joltAdapters.size(); j++)
        {

            //check to see if the current adapter can reach the next adapter
            //if so, add the possible number of paths to it
            if (joltAdapters[j] - joltAdapters[i] <= 3)
            {
                path[i] += path[j];
            }

            //otherwise break, and move backwards
            else
            {
                break;
            }
        }
    }

    //first index in dp array should have total number of paths
    ans = path[0];

    cout << "Ans is: " << ans << endl;
    return ans;
}