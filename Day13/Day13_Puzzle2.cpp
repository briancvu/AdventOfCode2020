#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
#include <numeric>

using namespace std;

long long gcd(long long int a, long long int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

long long lcm(long long int a, long long int b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    ifstream file("busTimes.txt");
    string line1, line2;
    vector<pair<int, int>> busTimes;

    //skip line 1
    getline(file, line1);

    //parse through line 2, and keep the index
    int i = 0;
    while (getline(file, line2))
    {
        istringstream iss(line2);
        while (iss.good())
        {
            string current;
            getline(iss, current, ',');

            //if x then skip, otherwise push into vector
            if (current == "x")
            {
            }
            else
            {
                int val = stoi(current);
                busTimes.push_back({val, i});
            }
            i++;
        }
    }
    file.close();

    //sort the busTimes vector so that we have the greatest tiem first
    sort(busTimes.begin(), busTimes.end());
    reverse(busTimes.begin(), busTimes.end());

    long int timestamp = busTimes[0].first - busTimes[0].second;
    long int step = busTimes[0].first;

    //search for a solution to each ID, and find the LCD of the current step and the ID
    for (auto times : busTimes)
    {
        while ((timestamp + times.second) % times.first != 0)
        {
            timestamp += step;
        }
        step = lcm(step, times.first);
    }
    long int ans = timestamp;
    cout << "Answer is: " << ans << endl;
    return timestamp;
}