//To solve day 14 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <map>

enum class cmd
{
    mask,
    mem
};

using Command = std::pair<cmd, std::optional<uint32_t>>;
using Instructions = std::vector<std::pair<Command, std::string>>;

Command StringToCommand(std::string const str_cmd)
{
    if (str_cmd == "mask")
        return {cmd::mask, {}};
    return {cmd::mem, std::stoi(str_cmd.substr(4, str_cmd.find("]") - 4))};
}

Instructions ReadInstructions(std::string const filename)
{
    Instructions instructions;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //each line has xxx = yyy
            std::string input_thing, input_thing2;
            infile >> input_thing;
            infile >> input_thing2;
            infile >> input_thing2;
            instructions.push_back({StringToCommand(input_thing), input_thing2});
        }
    }
    infile.close();
    return instructions;
}

uint64_t Mask(uint64_t number, std::string const &mask)
{
    uint64_t result = 0;
    for (int i = 0; i < mask.size(); i++)
    {
        if (mask[mask.size() - 1 - i] == '0')
            result += 0;
        else if (mask[mask.size() - 1 - i] == '1')
            result += uint64_t(std::pow(2, i));
        else
            result += (number % 2) * uint64_t(std::pow(2, i));
        number = number / 2;
    }
    return result;
}

std::string Mask2(uint64_t number, std::string const &mask)
{
    std::string result = "000000000000000000000000000000000000";
    for (int i = 0; i < mask.size(); i++)
    {
        if (mask[mask.size() - 1 - i] == '0')
            result[mask.size() - 1 - i] = std::to_string(number % 2)[0];
        else
            result[mask.size() - 1 - i] = mask[mask.size() - 1 - i];
        number = number / 2;
    }
    return result;
}

std::map<uint32_t, uint64_t> ProcessInstructions(Instructions const &instructions)
{
    //The idea is to loop over all instructions and do as they say
    //init mask
    std::string mask;
    std::map<uint32_t, uint64_t> addresses;
    for (auto instruction : instructions)
    {
        switch (instruction.first.first)
        {
        case cmd::mask:
            mask = instruction.second;
            break;
        case cmd::mem:
            addresses[instruction.first.second.value()] = Mask(std::stoi(instruction.second), mask);
            break;
        }
    }
    return addresses;
}

uint64_t BinstringToNumber(std::string const &s)
{
    uint64_t result = 0;
    for (unsigned int i = 0; i < s.size(); i++)
    {
        result += uint64_t(s[s.size() - 1 - i] - 48) * uint64_t(std::pow(2, i));
    }
    return result;
}

std::vector<uint64_t> GetAllAddresses(std::string str_binary, uint32_t const index = 0)
{
    //Recursive function to compute sum off all possiblities given a string
    //The index takes into account where to start counting (from the right) as this is a recursive function
    std::vector<uint64_t> result;
    if (index == str_binary.size()) //End the recursion
        return {BinstringToNumber(str_binary)};
    if (str_binary[str_binary.size() - 1 - index] == 'X')
    {
        str_binary[str_binary.size() - 1 - index] = '0';
        auto _res = GetAllAddresses(str_binary, index + 1);
        result.insert(result.end(), _res.begin(), _res.end());
        str_binary[str_binary.size() - 1 - index] = '1';
        _res = GetAllAddresses(str_binary, index + 1);
        result.insert(result.end(), _res.begin(), _res.end());
    }
    else
    {
        auto _res = GetAllAddresses(str_binary, index + 1);
        result.insert(result.end(), _res.begin(), _res.end());
    }

    return result;
}

std::map<uint64_t, uint64_t> ProcessInstructions2(Instructions const &instructions)
{
    //The idea is to loop over all instructions and do as they say
    //init mask
    std::string mask;
    std::map<uint64_t, uint64_t> addresses;
    for (auto instruction : instructions)
    {
        switch (instruction.first.first)
        {
        case cmd::mask:
            mask = instruction.second;
            break;
        case cmd::mem:
            auto addresses_v = GetAllAddresses(Mask2(instruction.first.second.value(), mask));
            for (auto address_v : addresses_v)
            {
                addresses[address_v] = std::stoi(instruction.second);
            }
            break;
        }
    }
    return addresses;
}

template <class Tk, class T>
T SumMap(std::map<Tk, T> const &_map)
{
    T sum = 0;
    for (auto _element : _map)
    {
        sum += _element.second;
    }
    return sum;
}

//Main function
int main()
{
    auto instructions = ReadInstructions("C:\\Users\\alex1\\git\\AdventOfCode\\day14\\input.txt");
    auto addresses = ProcessInstructions(instructions);
    auto result = SumMap(addresses);

    auto addresses2 = ProcessInstructions2(instructions);
    auto result2 = SumMap(addresses2);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}