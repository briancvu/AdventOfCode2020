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

int main()
{
    ifstream file("BagRules.txt");
    string str;
    string name;
    int ans = 0;

    map<string, list<string>> graph;

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

        //iss >> name skips over the number of bags
        while (iss >> name || !iss.eof())
        {

            //get the color of the bags
            getline(iss, subsequentBags, ',');

            //remove any leading whitespace, and the trailing 'bag' or 'bags' characters
            int firstPosition = subsequentBags.find_first_not_of(' ');
            int lastPosition = subsequentBags.find_last_of(' ');
            subsequentBags = subsequentBags.substr(firstPosition, lastPosition - 1);
            graph[firstBag].push_back(subsequentBags);
        }
    }
    file.close();

    //iterate through graph
    for (auto it = graph.begin(); it != graph.end(); ++it)
    {
        //if name is shiny gold, skip as we are in the shiny gold bag
        if (it->first == "shiny gold")
        {
            continue;
        }

        //create a possible bags "queue" to push bags onto
        list<string> possible_bags = {it->first};

        //while possible bags queue is not empty
        while (possible_bags.size() > 0)
        {
            string front = possible_bags.front();

            //if subsequent bag contains shiny gold, increment and move to next bag
            if (front == "shiny gold")
            {
                ans++;
                break;
            }

            //push all subsequent bags onto the possible bags"queue"
            for (auto nextIT : graph[front])
            {
                possible_bags.push_back(nextIT);
            }
            possible_bags.pop_front();
        }
    }

    cout << "Number of bags is: " << ans << endl;
    return ans;
}