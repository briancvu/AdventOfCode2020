#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define LLONG_MAX 9223372036854775807

using namespace std;

int main()
{
    ifstream file("Preamble.txt");
    string str;
    long long ans = 0;

    //create sliding window params
    int front = 0;
    int back = 1;

    //create current value and value to find
    long long curVal = 0;
    long long valToFind = 1038347917;

    //create vectors for holding full list
    vector<long long> data;

    //push file into a vector
    while (getline(file, str))
    {
        //cout << str << endl;
        data.push_back(stoll(str));
    }

    //add the first two values to curVal
    curVal += data[front];
    curVal += data[back];

    //create min and max value
    long long minVal = LLONG_MAX;
    long long maxVal = 0;

    while (curVal != valToFind)
    {

        //if value is too low, add the next value and increment
        if (curVal < valToFind)
        {
            back++;
            curVal += data[back];
            cout << "Back val: " << data[back] << endl;
            cout << "Cur val: " << curVal << endl;
        }

        //if value is too high, subtract the first value and increment
        else if (curVal > valToFind)
        {
            curVal = curVal - data[front];
            front++;
            cout << "Front val: " << data[front] << endl;
            cout << "Cur val: " << curVal << endl;
        }

        //otherwise we have found the value and break
        else
        {
            break;
        }
    }

    //parse through sliding window to find min and max
    for (int i = front; i <= back; i++)
    {
        if (data[i] < minVal)
        {
            minVal = data[i];
        }
        if (data[i] > maxVal)
        {
            maxVal = data[i];
        }
    }
    ans = minVal + maxVal;
    cout << "ANSWER: " << ans << endl;

    return 0;
}