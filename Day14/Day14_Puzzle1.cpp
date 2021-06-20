#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string decToBinary(int n)
{

    // //saving into an array
    // int binaryNum[32];
    // int i = 0;
    // string str = ""
    // while(n > 0){
    //     binaryNum[i] = n%2;
    //     n = n/2;
    //     i++;
    // }
    if (n == 0)
    {
        return "0";
    }

    //saving into a string
    string str;
    while (n != 0)
    {
        str = (n % 2 == 0 ? "0" : "1") + str;
        n /= 2;
    }
    return str;
}

int binaryToDec(int n)
{
    int num = n;
    int dec_value = 0;

    //initizaling base value to 1
    int base = 1;

    int temp = num;
    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}

int main()
{

    ifstream file("bitmaskSystem.txt");
    string str;
    int ans = 0;

    //unsigned short for bitmask
    string bitmask;

    //variables for values pulled from bitmask & val
    string bitVal;
    int decBitVal;

    //variables for array of memorylocations
    int memLoc;
    unordered_map<int, int> memLocMap;

    while (getline(file, str))
    {
        if (str.find("mask") != string::npos)
        {

            //create bitmask from first position
            //use string to unsigned long, then cast
            bitmask = str.substr(7);
        }
        else
        {

            //pull memory address
            memLoc = stoi(str.substr(4));

            //parse value
            bitVal = decToBinary(stoi(str.substr(9)));
            int i = 0;
            for (int i = 0; i < bitmask.size(); i++)
            {
                if (bitmask[i] == '1' || bitmask[i] == '0')
                {
                    bitVal[i] = bitmask[i];
                }
            }

            decBitVal = binaryToDec(stoi(bitVal));
            cout << decBitVal << endl;
            memLocMap[memLoc] = decBitVal;
        }
    }

    for (auto it = memLocMap.begin(); it != memLocMap.end(); it++)
    {
        ans += it->second;
    }

    cout << "Answer is:" << ans;
    return ans;
}