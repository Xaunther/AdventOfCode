//To solve day 17 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <list>

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

std::vector<std::string> AddAll(std::vector<std::list<std::string>> const &combinations, uint32_t const depth = 0, std::string prev = "")
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

std::list<std::string> GetAllPosibilities(Rules &rules, uint32_t const rule_N)
{
    if (rules[rule_N].find("\"") != std::string::npos) //Final character rule
        return {rules[rule_N].substr(1, rules[rule_N].size() - 2)};

    std::list<std::string> result;
    //Split by "ORS"
    auto possibilities = SplitString(rules[rule_N], " | ");
    for (auto possibility : possibilities)
    {
        std::vector<std::list<std::string>> combinations;
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

bool IsMatching(std::string const &message, std::list<std::string> const &possibilities)
{
    for (auto possibility : possibilities)
    {
        if (possibility == message)
            return true;
    }
    return false;
}

bool IsMatching2(std::string message, std::list<std::string> const &possibilities_x, std::list<std::string> const &possibilities_y)
{
    uint32_t used_x = 0;
    uint32_t used_y = 0;
    bool use_y = false;
    while (message != "")
    {
        bool res;
        if (!use_y) //Use X
            res = IsMatching(message.substr(0, possibilities_x.begin()->size()), possibilities_x);
        else //Use y
            res = IsMatching(message.substr(0, possibilities_x.begin()->size()), possibilities_y);
        //If it has been matched, remove that part from message, add to counter and switch to y if near the end
        if (res)
        {
            if (use_y)
                used_y++;
            else
                used_x++;
            message = message.substr(possibilities_x.begin()->size());
            if (message.size() == possibilities_x.begin()->size())
                use_y = true;
        }
        else //If not found, switch to y if not there yet, otherwise we failed
        {
            if (use_y)
                return false;
            else
                use_y = true;
        }
    }
    //Now, we must use at least 1 of each x and y and at least one more x than y
    if (used_x > used_y && used_y > 0)
        return true;
    else
        return false;
}

uint32_t CountMatching(Messages const &messages, std::list<std::string> const &possibilities)
{
    uint32_t result = 0;
    for (auto message : messages)
        result += (int)IsMatching(message, possibilities);
    return result;
}

uint32_t CountMatching2(Rules &rules, Messages const &messages, std::list<std::string> const &possibilities_x, std::list<std::string> const &possibilities_y)
{
    uint32_t result = 0;
    for (auto message : messages)
        result += (int)IsMatching2(message, possibilities_x, possibilities_y);
    return result;
}

//Main function
int main()
{
    Rules rules;
    Messages messages;
    ReadInput("C:\\Users\\alex1\\git\\AdventOfCode\\day19\\input.txt", rules, messages);
    auto possibilities = GetAllPosibilities(rules, 0);
    auto result = CountMatching(messages, possibilities);

    //We change these two rules and get the possibilities for x and y
    rules[8] = "\"x\"";
    rules[11] = "\"xy\"";
    auto possibilities_x = GetAllPosibilities(rules, 42);
    auto possibilities_y = GetAllPosibilities(rules, 31);

    //This is convenient, the number we're looking at is just xxy, with x being rule 42 and y rule 31 times, repeated a number of times
    auto result2 = CountMatching2(rules, messages, possibilities_x, possibilities_y);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
