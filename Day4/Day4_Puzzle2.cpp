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

    //create vector of valid passports
    vector<unordered_map<string, string>> validPassports;
    unordered_map<string, string> values;

    while (getline(file, str))
    {
        int i = 0;
        string fieldName = "";
        string fieldVal = "";

        //for empty lines, check if we have a valid passport
        if (str.empty())
        {
            if (values.size() >= 8)
            {
                validPassports.push_back(values);
            }
            else if (values.size() == 7)
            {
                if (values.find("cid") == values.end())
                {
                    validPassports.push_back(values);
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
            values[fieldName] = fieldVal;
        }
    }

    //run checker once more for last passport
    if (!values.empty())
    {
        if (values.size() >= 8)
        {
            validPassports.push_back(values);
        }
        else if (values.size() == 7)
        {
            if (values.find("cid") == values.end())
            {
                validPassports.push_back(values);
            }
        }
    }

    //create list of valid eye colors
    vector<string> validEyeColors = {
        "amb",
        "blu",
        "brn",
        "gry",
        "grn",
        "hzl",
        "oth"};

    //run through list of valid passports to check for validity
    for (int i = 0; i < validPassports.size(); i++)
    {
        string birthYear = validPassports[i]["byr"];
        string issueYear = validPassports[i]["iyr"];
        string expirationYear = validPassports[i]["eyr"];
        string height = validPassports[i]["hgt"];
        string hairColor = validPassports[i]["hcl"];
        string eyeColor = validPassports[i]["ecl"];
        string passportID = validPassports[i]["pid"];

        //check for birthYear, issueYear, and expirationYear length
        if (birthYear.length() != 4 || issueYear.length() != 4 || expirationYear.length() != 4)
        {
            continue;
        }

        int birthYearVal = stoi(birthYear);
        int issueYearVal = stoi(issueYear);
        int expirationYearVal = stoi(expirationYear);

        //check birthYear, issueYear, and expirationYear value
        if (birthYearVal < 1920 || birthYearVal > 2002 || issueYearVal < 2010 || issueYearVal > 2020 || expirationYearVal < 2020 || expirationYearVal > 2030)
        {
            //cout << "This is true when birthYearVal is: " << birthYearVal << "  or issueYearVal is: " << issueYearVal << " or expirationYearVal is: " << expirationYearVal << endl;
            continue;
        }

        //check for height vailidity
        if (height[height.length() - 2] == 'c' && height[height.length() - 1] == 'm')
        {
            cout << "Height is:" << height << endl;
            string heightCMString = height.substr(0, height.length() - 2);
            cout << "Height substring is: " << heightCMString << endl;
            int heightCM = stoi(heightCMString);
            if (heightCM < 150 || heightCM > 193)
            {
                continue;
            }
        }
        else if (height[height.length() - 2] == 'i' && height[height.length() - 1] == 'n')
        {
            string heightINString = height.substr(0, height.length() - 2);
            int heightIN = stoi(heightINString);
            if (heightIN < 59 || heightIN > 76)
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        //check if hair color is valid
        bool hairColorValid = true;
        if (hairColor.length() != 7 || hairColor[0] != '#')
        {
            continue;
        }

        for (int j = 1; j < hairColor.length(); j++)
        {
            if ((hairColor[j] >= '0' && hairColor[j]) <= '9' ||
                (hairColor[j] >= 'a' && hairColor[j] <= 'f'))
            {
                continue;
            }
            hairColorValid = false;
        }

        if (!hairColorValid)
        {
            continue;
        }

        //check if eye color is valid
        if (find(validEyeColors.begin(), validEyeColors.end(), eyeColor) == validEyeColors.end())
        {
            continue;
        }

        //check if passportID is valid

        if (passportID.length() != 9 || (passportID.find_first_not_of("0123456789") != string::npos))
        {
            continue;
        }
        ans++;
    }

    cout << ans << endl;
    return ans;
}