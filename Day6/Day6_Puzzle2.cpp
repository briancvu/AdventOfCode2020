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
    int curRows = 0;

    //create hashmap to hold number of questions answered per group
    unordered_map<char, int> questions;
    unordered_map<char, int>::iterator it;

    while (getline(file, str))
    {

        //for a new line, check hashmap to see how many answers to add
        if (str.empty())
        {

            //check if number of questions answered equals numbers of rows
            //if so add, that means all parties answered the question
            int allAnswered = 0;
            for (it = questions.begin(); it != questions.end(); it++)
            {
                if (it->second == curRows)
                {
                    allAnswered++;
                }
            }
            totalAnswered += allAnswered;
            questions.clear();
            curRows = 0;
            continue;
        }

        //if not an empty row, add to row counter
        curRows++;

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

            //if it does not exist, initialize the count to 1
            if (questions.find(str[i]) == questions.end())
            {
                questions[str[i]] = 1;
            }

            //else add 1 to the current count
            else
            {
                questions[str[i]]++;
            }
        }
    }

    //run one more iteration for last group that does not have a new line
    int allAnswered = 0;
    for (it = questions.begin(); it != questions.end(); it++)
    {
        if (it->second == curRows)
        {
            allAnswered++;
        }
    }
    totalAnswered += allAnswered;
    questions.clear();
    curRows = 0;

    cout << "Number of questions answered are: " << totalAnswered << endl;
    return totalAnswered;
}