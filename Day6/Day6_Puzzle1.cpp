#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
    ifstream file("QuestionsAnswered.txt");
    string str;
    int totalAnswered = 0;

    //create hashmap to hold number of questions answered per group
    unordered_map<char, int> questions;

    while (getline(file, str))
    {

        //when a new line is reached, add all questions answered and reset hashmap
        if (str.empty())
        {
            totalAnswered += questions.size();
            questions.clear();
            continue;
        }

        //create string stream to read line
        istringstream iss(str);
        string curLine;
        while (!iss.eof())
        {
            getline(iss, curLine);
        }

        //check all characters in a line to see how many questions are answered
        for (int i = 0; i < curLine.length(); i++)
        {
            if (questions.find(str[i]) == questions.end())
            {
                questions[str[i]] = 0;
            }
            else
            {
                questions[str[i]]++;
            }
        }
    }

    //run one more iteration for last group that does not have a new line
    totalAnswered += questions.size();
    questions.clear();

    cout << "Number of questions answered are: " << totalAnswered << endl;
    return totalAnswered;
}