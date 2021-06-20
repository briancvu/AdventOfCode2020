#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class passport
{
public:
};

int main()
{
    ifstream file("Passports.txt");
    string str;
    int ans = 0;

    vector<string> passports;
    unordered_map<string, string> values;

    while (getline(file, str))
    {
        int i = 0;
        string fieldName = "";
        string fieldVal = "";

        //for empty lines, check if we have a valid passport
        if (str.empty())
        {
            cout << "Current count is: " << ans << endl;
            cout << endl;
            if (values.size() >= 8)
            {
                ans++;
            }
            else if (values.size() == 7)
            {
                if (values.find("cid") == values.end())
                {
                    ans++;
                }
            }
            else
            {
            }

            values.clear();
            continue;
        }

        //create stringstream for current line
        istringstream iss(str);

        //while not end of line, extract all values and insert into hashmap
        while (!iss.eof())
        {
            getline(iss, fieldName, ':');
            getline(iss, fieldVal, ' ');
            cout << "FieldName is:" << fieldName << endl;
            cout << "FieldValue is:" << fieldVal << endl;
            values[fieldName] = fieldVal;
        }
    }

    //run checker once more for last passport
    if (!values.empty())
    {
        if (values.size() >= 8)
        {
            ans++;
        }
        else if (values.size() == 7)
        {
            if (values.find("cid") == values.end())
            {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return ans;
}