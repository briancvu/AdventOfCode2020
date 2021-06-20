#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>
#include <stack>
#include <set>
using namespace std;

struct Bag
{
    string bagName;
    vector<string> bagRules;
};

bool containsShinyGold(Bag startingBag)
{
    for (int i = 0; i < startingBag.bagRules.size(); i++)
    {
        Bag subBag;
        if (startingBag.bagRules[i] == "shiny gold")
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream file("BagRules.txt");
    string str;
    string name;
    int ans = 0;

    map<string, list<string>> graph;
    vector<Bag> allBags;
    set<string> firstBags;

    while (getline(file, str))
    {
        Bag currBag;

        string firstBag = "";
        string subsequentBags = "";

        //find the first bag by getting substring until text bags
        firstBag = str.substr(0, str.find("bags"));
        firstBag = firstBag.substr(0, firstBag.length() - 1);
        cout << firstBag << endl;
        //currBag.bagName = firstBag;
        firstBags.insert(firstBag);
        //cout << "Bag name is: " << currBag.bagName << endl;

        //skip over word contain to get subsequent bags
        int pos = str.find("contain");
        pos = pos + 7;

        istringstream iss(str.substr(pos));

        //iss >> name skips over the number of bags
        while (iss >> name || !iss.eof())
        {
            /*cout << name << endl;
            if (name == "no")
            {
                graph[firstBag].push_back(name);
                continue;
            }*/

            //get the color of the bags
            getline(iss, subsequentBags, ',');

            //remove any leading whitespace, and the trailing 'bag' or 'bags' characters
            int firstPosition = subsequentBags.find_first_not_of(' ');
            int lastPosition = subsequentBags.find_last_of(' ');
            //int value = stoi(name);
            //cout << name << endl;
            subsequentBags = subsequentBags.substr(firstPosition, lastPosition - 1);
            //currBag.bagRules.push_back(subsequentBags);

            graph[firstBag].push_back(subsequentBags);
            //cout << "SubsequentBags are:" << subsequentBags << endl;
        }
        //allBags.push_back(currBag);
    }
    file.close();

    //print adjacency list for graph
    /*for (auto &value : graph)
    {
        string vertex = value.first;
        list<string> adjacentVertices = value.second;
        list<string>::iterator it = adjacentVertices.begin();

        cout << "Adjacency List of " << vertex << "is: ";
        while (it != adjacentVertices.end())
        {
            cout << (*it) << " ";
            ++it;
        }
        cout << endl;
    }*/

    //prints adjacency lists for Bags
    /*for (int i = 0; i < allBags.size(); i++)
    {
        int bagRulesLength = allBags[i].bagRules.size();
        cout << "Adjacency List for: " << allBags[i].bagName << " is: ";
        for (int j = 0; j < bagRulesLength; j++)
        {
            cout << allBags[i].bagRules[j] << " ";
        }
        cout << endl;
    }*/

    for (string bag : firstBags)
    {
        //cout << bag << ": ";
        //if current bag is shiny gold skip
        if (bag == "shiny gold")
        {
            continue;
        }

        list<string> possible_bags = {bag};
        while (possible_bags.size() > 0)
        {
            string front = possible_bags.front();

            //we found a gold bag, move to next
            if (front == "shiny gold")
            {
                ans++;
                break;
            }

            //add extra bags to check
            for (auto it : graph[front])
            {
                //cout << it << " ";
                possible_bags.push_back(it);
            }
            //cout << endl;
            possible_bags.pop_front();
        }
    }

    cout << "Number of bags is: " << ans << endl;
    return ans;
}