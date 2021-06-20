#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    ifstream file("Preamble.txt");
    string str;
    long long ans;

    //create vectors for holding full list and preamble
    vector<long long> preamble;
    vector<long long> data;

    //push file into a vector
    while (getline(file, str))
    {
        //cout << str << endl;
        data.push_back(stoll(str));
    }

    //push first 25 values into preamble
    for (int i = 0; i < 25; i++)
    {
        preamble.push_back(data[i]);
        //cout << data[i] << endl;
    }

    for (int i = 25; i < data.size(); i++)
    {
        //sort preamble vector every time
        sort(preamble.begin(), preamble.end());

        int j = 0, k = 24;

        while (j < k)
        {

            //if lowest + highest value is too high, decrement the high value
            if (preamble[j] + preamble[k] > data[i])
            {
                k--;
            }

            //if lowest + highest value is too low, increment the low value
            else if (preamble[j] + preamble[k] < data[i])
            {
                j++;
            }

            //otherwise, we have found a pair and break
            else if (preamble[j] + preamble[k] == data[i])
            {
                break;
            }
        }

        //if j == k then we have tried all values, print out the invalid value
        if (j == k)
        {
            ans = data[i];
            cout << "Answer is: " << ans << endl;
            return ans;
        }

        //remove the i-25 index, and add the current value to preamble
        vector<long long>::iterator position = find(preamble.begin(), preamble.end(), data[i - 25]);
        if (position != preamble.end())
        {
            preamble.erase(position);
        }
        preamble.push_back(data[i]);
    }

    //if we reach here, code is wrong
    cout << "Found nothing" << endl;
    return 0;
}