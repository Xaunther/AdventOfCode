//To solve day 6 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

//Alias for bagrules class
using BagContains = std::vector<std::pair<unsigned int, std::string>>;
using BagRules = std::map<std::string, BagContains>;

BagRules ReadBagRules(std::string filename)
{
    BagRules bagrules;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //Read bag rules. 1 rule per line
            std::string input_thing;
            std::getline(infile, input_thing);
            std::string input_key;
            BagContains input_contains;
            //The key first
            input_key = input_thing.substr(0, input_thing.find(" bags"));
            //Now loop for each possible container
            size_t pos = input_thing.find(" bags") + 12;
            do
            {
                std::string raw_rule = input_thing.substr(pos + 2, input_thing.find(" bag", pos) - pos - 2);
                pos = input_thing.find(",", pos + 1);
                if (raw_rule.find("no other") != std::string::npos)
                {
                    input_contains.push_back({0, ""});
                }
                else
                {
                    //number -space- bag string
                    input_contains.push_back({stoi(raw_rule.substr(0, raw_rule.find(" "))), raw_rule.substr(raw_rule.find(" ") + 1)});
                    //std::cout << input_contains[input_contains.size() - 1].first << ", " << input_contains[input_contains.size() - 1].second << std::endl;
                }
            } while (pos != std::string::npos);
            bagrules.insert(std::pair<std::string, BagContains>{input_key, input_contains});
        }
    }
    return bagrules;
}

bool IsInBag(BagRules &bagrules, std::pair<std::string, BagContains> bagrule, std::pair<unsigned int, std::string> bagsearch)
{
    if (bagrule.second[0].first == 0) //No other bags inside
    {
        //std::cout << "Reached empty bag: " << bagrule.first + "." << std::endl;
        return false;
    }
    //look for a match
    for (auto insidebags : bagrule.second)
    {
        if (insidebags.second == bagsearch.second)
        {
            //std::cout << "Found match in " << bagrule.first + "." << std::endl;
            return true;
        }
    }
    //Keep looking
    for (auto insidebags : bagrule.second)
    {
        //std::cout << "Looking at " << insidebags.second + "." << std::endl;
        //std::cout << "cca:" << bagrules[insidebags.second][0].second + "." << std::endl;
        if (IsInBag(bagrules, {insidebags.second, bagrules[insidebags.second]}, bagsearch))
            return true;
    }
    return false;
}

unsigned int GetContainerBags(BagRules &bagrules, std::pair<unsigned int, std::string> bagsearch)
{
    unsigned int result = 0;
    for (auto bagrule : bagrules)
    {
        //std::cout << "Looking at " << bagrule.first + "." << std::endl;
        result += (int)IsInBag(bagrules, bagrule, bagsearch);
    }
    return result;
}

unsigned int GetBagsIn(BagRules &bagrules, std::pair<unsigned int, std::string> bagsearch)
{
    unsigned int result = 0;
    //std::cout << "Searching:" + bagsearch.second + "." << std::endl;
    for (auto bagrule : bagrules[bagsearch.second])
    {
        if (bagrule.first == 0) //If no more bags inside, just return the number of final bags required
        {
            //std::cout << "Returning:" << bagsearch.first << std::endl;
            return 0;
        }
        result += GetBagsIn(bagrules, bagrule) + bagrule.first;
    }
    //std::cout << "Returning:" << result * bagsearch.first << std::endl;
    return result * bagsearch.first;
}

//Main function
int main()
{
    BagRules bagrules = ReadBagRules("C:\\Users\\alex1\\git\\AdventOfCode\\day7\\input.txt");
    unsigned int result = GetContainerBags(bagrules, {1, "shiny gold"});
    unsigned int result2 = GetBagsIn(bagrules, {1, "shiny gold"});

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}