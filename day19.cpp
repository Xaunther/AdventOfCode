//To solve day 17 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using Rule = std::pair<uint32_t, std::string>;
using Rules = std::map<uint32_t, std::string>;
using Messages = std::vector<std::string>;

std::vector<std::string> SplitString(std::string const &s, std::string const pattern)
{
    if (s.find(pattern) == std::string::npos)
        return {s};

    std::vector<std::string> s_list;
    size_t i = 0;
    while (s.find(pattern, i) != std::string::npos)
    {
        s_list.push_back(s.substr(i, s.find(pattern, i) - i));
        i = s.find(pattern, i) + pattern.size();
    }
    //Add last
    s_list.push_back(s.substr(i));
    return s_list;
}

void ReadInput(std::string const &filename, Rules &rules, Messages &messages)
{
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return;

    //Read rules
    std::string input_thing;
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        std::vector<std::string> input_split = SplitString(input_thing, ": ");
        rules[std::stoi(input_split[0])] = input_split[1];
        input_thing = "";
        std::getline(infile, input_thing);
    }

    //Read messages
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        messages.push_back(input_thing);
        input_thing = "";
        std::getline(infile, input_thing);
    }
    infile.close();

    return;
}

std::vector<std::string> AddAll(std::vector<std::vector<std::string>> const &combinations, uint32_t const depth = 0, std::string prev = "")
{
    if (depth >= combinations.size())
        return {prev};
    std::vector<std::string> result;
    for (auto c : combinations[depth])
    {
        auto res = AddAll(combinations, depth + 1, prev + c);
        for (auto r : res)
            result.push_back(r);
    }
    return result;
}

std::vector<std::string> GetAllPosibilities(Rules &rules, uint32_t const rule_N)
{
    if (rules[rule_N].find("\"") != std::string::npos) //Final character rule
        return {rules[rule_N].substr(1, 1)};

    std::vector<std::string> result;
    //Split by "ORS"
    auto possibilities = SplitString(rules[rule_N], " | ");
    for (auto possibility : possibilities)
    {
        std::vector<std::vector<std::string>> combinations;
        auto iter_rules = SplitString(possibility, " ");
        for (auto iter_rule : iter_rules)
            combinations.push_back(GetAllPosibilities(rules, std::stoi(iter_rule)));
        auto pos_results = AddAll(combinations);
        //Append all these at the end
        for (auto pos_result : pos_results)
            result.push_back(pos_result);
    }
    return result;
}

bool IsMatching(std::string const &message, std::vector<std::string> const &possibilities)
{
    for (auto possibility : possibilities)
    {
        if (possibility == message)
            return true;
    }
    return false;
}

uint32_t CountMatching(Messages const &messages, std::vector<std::string> const &possibilities)
{
    uint32_t result = 0;
    for (auto message : messages)
        result += (int)IsMatching(message, possibilities);
    return result;
}

//Main function
int main()
{

    Rules rules;
    Messages messages;
    ReadInput("C:\\Users\\alex1\\git\\AdventOfCode\\day19\\input.txt", rules, messages);
    std::vector<std::string> possibilities = GetAllPosibilities(rules, 0);

    auto result = CountMatching(messages, possibilities);

    std::cout << "Result: " << result << std::endl;
    //std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
