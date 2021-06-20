#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;

int main()
{
    ifstream file("Passwords.txt");
    string str;
    int result = 0;

    vector<int> minimums;
    vector<int> maximums;
    vector<char> letters;
    vector<string> phrases;

    while (getline(file, str))
    {
        int i = 0;
        int lineSize = str.length();

        //create minimum value, and append to it as needed
        string minVal;
        while (str[i] != '-')
        {
            minVal += str[i];
            i++;
        }

        //push minimum value into min vector, and move increment up
        minimums.push_back(stoi(minVal, nullptr, 0));
        i++;

        //create maximum value, and append to it as needed
        string maxVal;
        while (str[i] != ' ')
        {
            maxVal += str[i];
            i++;
        }

        //push maximum value into max vector, and move increment up
        maximums.push_back(stoi(maxVal, nullptr, 0));
        i++;

        //push letter into letters vector and increment up
        letters.push_back(str[i]);
        i = i + 3;

        //create phrases value
        string phrase;
        while (i < lineSize)
        {
            phrase += str[i];
            i++;
        }

        //push phrase into phrase vector
        phrases.push_back(phrase);
    }

    //check if phrases[i] contains >= min[i] and <= max[i] letters[i]
    for (int i = 0; i < phrases.size(); i++)
    {
        int curLetterVal = 0;
        for (int j = 0; j < phrases[i].size(); j++)
        {
            if (phrases[i][j] == letters[i])
            {
                curLetterVal++;
            }
        }
        if (curLetterVal >= minimums[i] && curLetterVal <= maximums[i])
        {
            result++;
        }
    }

    cout << result << endl;
    return result;
}