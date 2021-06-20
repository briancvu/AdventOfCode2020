#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

//function to parse text file
void parseFile(ifstream &file, int &earliestTimestamp, vector<int> &busTimes)
{
    string str;

    int i = 0;
    while (getline(file, str))
    {
        istringstream iss(str);
        //for first line, get the earlist timestamp
        if (i == 0)
        {
            earliestTimestamp = stoi(str);
            i++;
        }

        //otherwise parse the bus times
        else
        {
            while (iss.good())
            {
                string current;
                getline(iss, current, ',');
                if (current == "x")
                {
                    continue;
                }
                else
                {
                    busTimes.push_back(stoi(current));
                }
            }
        }
    }
    file.close();
}

int main()
{
    ifstream file("busTimes.txt");
    int earliestTimestamp = 0;
    int ans = 0;
    vector<int> busTimes;

    //create variables for the index of the earliest bus we can catch
    //and the value of how close the bus time is
    int minIndex = INT_MAX;
    int minVal = INT_MAX;

    parseFile(file, earliestTimestamp, busTimes);
    for (int i = 0; i < busTimes.size(); i++)
    {

        //check for bus time closeness by subtracting the bus time and the mod
        int mod = earliestTimestamp % busTimes[i];
        if ((busTimes[i] - mod) < minVal)
        {
            minVal = busTimes[i] - mod;
            minIndex = i;
        }
    }

    //calculate answer with product of difference in mod and value, as well as the value
    ans = minVal * busTimes[minIndex];
    cout << "Answer is: " << ans << endl;

    return ans;
}