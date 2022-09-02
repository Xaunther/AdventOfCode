//To solve day 13 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using BusData = std::pair<uint64_t, std::vector<uint64_t>>;

std::vector<std::string> SplitString(std::string const s, std::string const pattern)
{
    if (s.find(pattern) == std::string::npos)
        return {s};

    std::vector<std::string> s_list;
    size_t i = 0;
    while (s.find(pattern, i) != std::string::npos)
    {
        s_list.push_back(s.substr(i, s.find(pattern, i) - i));
        i = s.find(pattern, i) + 1;
    }
    //Add last
    s_list.push_back(s.substr(i));
    return s_list;
}

std::vector<uint64_t> TrimBuses(std::vector<std::string> const raw_buses)
{
    std::vector<uint64_t> trimmed_buses;
    for (auto raw_bus : raw_buses)
    {
        if (raw_bus == "x")
            trimmed_buses.push_back(0);
        else
            trimmed_buses.push_back(stoi(raw_bus));
    }
    return trimmed_buses;
}

BusData ReadBusData(std::string const filename)
{
    BusData busdata;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        //2 lines to read
        infile >> busdata.first;
        std::string input_line;
        infile >> input_line;
        //Bus lines
        getline(infile, input_line);
        busdata.second = TrimBuses(SplitString(input_line, ","));
    }
    infile.close();
    return busdata;
}

std::pair<uint64_t, uint64_t> GetBusAndWaitTime(BusData const &busdata)
{
    std::pair<uint64_t, uint64_t> result = {busdata.second[0], busdata.second[0]};
    for (auto bus : busdata.second)
    {
        if (bus == 0)
            continue;
        if (bus - (busdata.first % bus) < result.second) //Less waiting time
        {
            result.first = bus;
            result.second = bus - (busdata.first % bus);
        }
    }
    return result;
}

void FindCommonWithOffset(std::pair<uint64_t, uint64_t> const &factors, unsigned int const &offset, uint64_t &t)
{
    while ((t + offset) % factors.second)
    {
        t += factors.first;
    }
    //std::cout << factors.first << ", " << factors.second << ", " << t << std::endl;
}

uint64_t FindEarliestConsecutive(BusData const &busdata)
{
    //So brute force is poor here, we need to scale up the thing
    //For that, we're gonna do pairings and find the t where they align at t, t+offset
    //Once found, we know those two lines will ONLY coincide again at their common factor, and they're prime numbers so we multiply
    //We now make a new pair with this number and next one... and so on, until we reach the end
    std::pair<uint64_t, uint64_t> factors;
    factors.first = busdata.second[0];
    uint64_t t = 0;
    for (unsigned int i = 1; i < busdata.second.size(); i++)
    {
        if (busdata.second[i] == 0)
            continue;
        factors.second = busdata.second[i];
        FindCommonWithOffset(factors, i, t); //t is changed
        factors.first = factors.first * factors.second;
    }
    return t;
}

//Main function
int main()
{
    BusData busdata = ReadBusData("C:\\Users\\alex1\\git\\AdventOfCode\\day13\\input.txt");
    auto result = GetBusAndWaitTime(busdata);
    auto result2 = FindEarliestConsecutive(busdata);

    std::cout << "Result: " << result.first << " * " << result.second << " = " << result.first * result.second << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}