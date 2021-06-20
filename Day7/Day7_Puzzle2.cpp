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

//recursive function dfs through bags and return total
int insideGoldBag(map<string, list<pair<string, int>>> graph, string bagName)
{

    //totalBags to start at 1 as a base multiplier
    int totalBags = 1;

    //create new list to hold bag and value
    list<pair<string, int>> currentBag = graph[bagName];

    for (auto it : currentBag)
    {
        totalBags += it.second * insideGoldBag(graph, it.first);
    }

    return totalBags;
}

int main()
{
    ifstream file("BagRules.txt");
    string str;
    string name;
    int ans = 0;

    map<string, list<pair<string, int>>> graph;

    while (getline(file, str))
    {

        string firstBag = "";
        string subsequentBags = "";

        //find the first bag by getting substring until text bags
        firstBag = str.substr(0, str.find("bags"));
        firstBag = firstBag.substr(0, firstBag.length() - 1);

        //skip over word contain to get subsequent bags
        int pos = str.find("contain");
        pos = pos + 7;

        istringstream iss(str.substr(pos));

        //another iss >> name skips over the number of bags
        while (iss >> name || !iss.eof())
        {

            //get the color of the bags
            getline(iss, subsequentBags, ',');

            //remove any leading whitespace, and the trailing 'bag' or 'bags' characters
            int firstPosition = subsequentBags.find_first_not_of(' ');
            int lastPosition = subsequentBags.find_last_of(' ');
            //cout << name << endl;

            if (isdigit(name[0]))
            {
                int value = stoi(name);
                //cout << name << endl;
                subsequentBags = subsequentBags.substr(firstPosition, lastPosition - 1);
                graph[firstBag].push_back(make_pair(subsequentBags, value));
            }
            else
            {
                graph[firstBag].push_back(make_pair("no other bags", 0));
            }

            //cout << "SubsequentBags are:" << subsequentBags << endl;
        }
    }
    file.close();

    //print adjacency list for graph
    // for (auto &value : graph)
    // {
    //     string vertex = value.first;
    //     list<pair<string, int>> adjacentVertices = value.second;
    //     list<pair<string, int>>::iterator it = adjacentVertices.begin();

    //     cout << "Adjacency List of " << vertex << " is: ";
    //     while (it != adjacentVertices.end())
    //     {
    //         cout << (*it).second << " ";
    //         cout << (*it).first << " ";
    //         ++it;
    //     }
    //     cout << endl;
    // }

    // ITERATIVE SOLUTION
    // list<pair<string, int>> possibleBags;
    // possibleBags.push_back({"shiny gold", 1});
    // while (possibleBags.size() > 0)
    // {
    //     pair<string, int> subBag = possibleBags.front();
    //     ans += subBag.second;

    //     for (auto it : graph[subBag.first])
    //     {
    //         possibleBags.push_back({it.first, it.second * subBag.second});
    //     }
    //     possibleBags.pop_front();
    // }

    // ans--;

    // RECURSIVE SOLUTION
    ans = insideGoldBag(graph, "shiny gold");

    //subtract 1 to get rid of initial bag
    ans--;

    cout << "Number of bags is: " << ans << endl;
    return ans;
}