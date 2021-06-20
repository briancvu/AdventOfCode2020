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

    //create two pointers
    int leftP = 0;
    int rightP = 0;

    while (rightP < joltAdapters.size())
    {

        //move up the pointers at every interation
        leftP = rightP;
        rightP++;

        //check for how big of a subset is found until there is a gap of 3
        while ((rightP < joltAdapters.size()) && (joltAdapters[rightP] != joltAdapters[rightP - 1] + 3))
        {
            rightP++;
        }

        //if gap is 3, number of permutations is 2
        if ((rightP - leftP) == 3)
        {
            ans *= 2;
        }

        //if gap is 4, number of permutations is 4
        else if ((rightP - leftP) == 4)
        {
            ans *= 4;
        }

        //if gap is 5, number of permutations is 5
        else if ((rightP - leftP) == 5)
        {
            ans *= 7;
        }

        //gaps of 2 have only permutation of 1 so the answer is mult by 1
        //gaps of >5 do not exist, but we could write a function for that
    }

    cout << "Ans is: " << ans << endl;
    return ans;
}