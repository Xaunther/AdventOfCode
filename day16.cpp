//To solve day 16 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

using Range = std::pair<uint32_t, uint32_t>;
using Ranges = std::pair<Range, Range>;

using Rule = std::pair<std::string, Ranges>;
using Rules = std::map<std::string, Ranges>;

using Ticket = std::vector<uint32_t>;
using Tickets = std::list<Ticket>;

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

Range StringToRange(std::string const &s)
{
    auto str_range = SplitString(s, "-");
    return {std::stoi(str_range[0]), std::stoi(str_range[1])};
}

Ranges StringToRanges(std::string const &s)
{
    auto str_ranges = SplitString(s, " or ");
    return {StringToRange(str_ranges[0]), StringToRange(str_ranges[1])};
}

Rule StringToRule(std::string const &s)
{
    auto str_rule = SplitString(s, ": ");
    return {str_rule[0], StringToRanges(str_rule[1])};
}

Ticket StringToTicket(std::string const &s)
{
    Ticket ticket;
    auto str_ticket = SplitString(s, ",");
    for (auto _ticket : str_ticket)
    {
        ticket.push_back(std::stoi(_ticket));
    }
    return ticket;
}

void ReadInput(std::string const &filename, Rules &rules, Ticket &myTicket, Tickets &tickets)
{
    std::ifstream infile;
    infile.open(filename.c_str());
    std::string input_line;
    if (!infile.is_open())
        return;
    //First we read the rules, line by line
    std::getline(infile, input_line);
    while (input_line != "")
    {
        rules.insert(StringToRule(input_line));
        std::getline(infile, input_line);
    }
    //Then we read OUR ticket
    std::getline(infile, input_line);
    std::getline(infile, input_line);
    myTicket = StringToTicket(input_line);

    //Read other tickets
    std::getline(infile, input_line);
    std::getline(infile, input_line);
    std::getline(infile, input_line);
    while (input_line != "")
    {
        tickets.push_back(StringToTicket(input_line));
        input_line = "";
        std::getline(infile, input_line);
    }
    //std::cout << rules.size() << std::endl;
    //std::cout << tickets.size() << std::endl;
    return;
}

bool InRange(uint32_t const &_t, Range const &range)
{
    if (_t >= range.first && _t <= range.second)
        return true;
    else
        return false;
}

bool IsPossible(uint32_t const &_t, Rule const &rule)
{
    if (InRange(_t, rule.second.first) || InRange(_t, rule.second.second))
        return true;
    else
        return false;
}

bool IsPossible(uint32_t const &_t, Rules const &rules)
{
    for (const auto rule : rules)
    {
        if (IsPossible(_t, rule))
            return true;
    }
    return false;
}

uint64_t GetScanningErrorRate(Ticket const &ticket, Rules const &rules)
{
    uint64_t result = 0;
    for (const auto _t : ticket)
    {
        if (!IsPossible(_t, rules))
            result += _t;
    }
    return result;
}

uint64_t GetScanningErrorRate(Tickets const &tickets, Rules const &rules)
{
    uint64_t result = 0;
    for (const auto ticket : tickets)
    {
        result += GetScanningErrorRate(ticket, rules);
    }
    return result;
}

bool IsPossible(Ticket const &ticket, Rules const &rules)
{
    for (const auto _t : ticket)
    {
        if (!IsPossible(_t, rules))
            return false;
    }
    return true;
}

void RemoveInvalidTickets(Tickets &tickets, Rules const &rules)
{
    for (auto ticket = tickets.begin(); ticket != tickets.end(); ticket++)
    {
        if (!IsPossible(*ticket, rules))
            tickets.erase(ticket);
    }
}

std::list<uint32_t> WhichCanMatch(Tickets const &tickets, Rule const &rule)
{
    std::list<uint32_t> result;
    for (uint32_t i = 0; i < tickets.begin()->size(); i++)
    {
        bool possible = true;
        for (const auto ticket : tickets)
        {
            if (!IsPossible(ticket[i], rule))
            {
                possible = false;
                break;
            }
        }
        if (possible)
            result.push_back(i);
    }
    result.sort();
    return result;
}

void Print(std::map<std::string, std::list<uint32_t>> const &map_results)
{
    std::cout << "_________________________________" << std::endl;
    for (const auto map_result : map_results)
    {
        std::cout << map_result.first << std::endl;
        std::cout << "-------" << std::endl;
        for (const auto n : map_result.second)
        {
            std::cout << n << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "_________________________________" << std::endl;
}

void RemoveElsewhere(std::map<std::string, std::list<uint32_t>> &map_results, std::pair<std::string, uint32_t> const _exception)
{
    for (auto map_result = map_results.begin(); map_result != map_results.end(); ++map_result)
    {
        if (map_result->first != _exception.first)
            map_result->second.remove(_exception.second);
        //else
        //std::cout << map_result->first << ", " << *map_result->second.begin() << std::endl;
    }
    //Print(map_results);
}

bool IsDetermined(std::map<std::string, std::list<uint32_t>> const &map_results)
{
    for (const auto map_result : map_results)
    {
        if (map_result.second.size() > 1)
            return false;
    }
    return true;
}

void TrimResults(std::map<std::string, std::list<uint32_t>> &map_results)
{
    //See if any entry has more than 1 possiblity
    for (const auto map_result : map_results)
    {
        if (map_result.second.size() == 1)
            RemoveElsewhere(map_results, {map_result.first, *map_result.second.begin()});
    }
    if (!IsDetermined(map_results))
        TrimResults(map_results);
}

uint64_t GetDepartureProduct(Tickets const &tickets, Rules const &rules, Ticket const &myTicket)
{
    //The idea is to fill a map for class -> vector index
    std::map<std::string, std::list<uint32_t>> map_results;
    //Let's try column by column
    for (const auto rule : rules)
    {
        map_results[rule.first] = WhichCanMatch(tickets, rule);
    }

    TrimResults(map_results);
    uint64_t result = 1;
    for (const auto map_result : map_results)
    {
        if (map_result.first.find("departure") != std::string::npos)
        {
            result = result * myTicket[*map_result.second.begin()];
            //std::cout << myTicket[*map_result.second.begin()] << std::endl;
        }
    }
    return result;
}

//Main function
int main()
{
    Ticket myTicket;
    Tickets tickets;
    Rules rules;
    ReadInput("C:\\Users\\alex1\\git\\AdventOfCode\\day16\\input.txt", rules, myTicket, tickets);

    auto result = GetScanningErrorRate(tickets, rules);
    std::cout << "Result: " << result << std::endl;
    RemoveInvalidTickets(tickets, rules);
    auto result2 = GetDepartureProduct(tickets, rules, myTicket);
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}