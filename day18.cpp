//To solve day 17 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

using Operation = std::pair<std::string, std::optional<uint64_t>>;
using Operations = std::vector<Operation>;

Operations ReadOperations(std::string const &filename)
{
    Operations operations;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return operations;

    std::string input_thing;
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        operations.push_back({input_thing, {}});
        input_thing = "";
        std::getline(infile, input_thing);
    }
    infile.close();
    return operations;
}

size_t FindMatchingParenthesis(std::string const &s, size_t start)
{
    if (start == std::string::npos)
        return start;
    uint32_t opened = 1;
    while (opened > 0 && start != std::string::npos)
    {
        if (s.find(")", start + 1) < s.find("(", start + 1)) //Closing this bracket
        {
            opened--;
            start = s.find(")", start + 1);
        }
        else //Opening another
        {
            opened++;
            start = s.find("(", start + 1);
        }
    }
    return start;
}

std::pair<size_t, size_t> FindFirstParenthesis(std::string const &s)
{
    std::pair<size_t, size_t> parenthesis;
    parenthesis.first = s.find("(");
    parenthesis.second = FindMatchingParenthesis(s, parenthesis.first);
    return parenthesis;
}

uint64_t Solve(std::string const &str)
{
    uint64_t result = 0;
    bool sum = true;
    for (size_t i = 0; i < str.size(); ++i)
    {
        auto j = FindMatchingParenthesis(str, i);
        if (str[i] == ' ')
            continue;
        else if (str[i] == '+')
            sum = true;
        else if (str[i] == '*')
            sum = false;
        else if (str[i] == '(')
        {
            if (sum)
                result = result + Solve(str.substr(i + 1, j - i - 1));
            else
                result = result * Solve(str.substr(i + 1, j - i - 1));
            i = j + 1;
        }
        else
        {
            if (sum)
                result = result + int(str[i] - 48);
            else
                result = result * int(str[i] - 48);
        }
    }
    return result;
}

void Solve(Operations &operations)
{
    for (auto &operation : operations)
    {
        operation.second = Solve(operation.first);
    }
}

uint64_t SumSolutions(Operations const &operations)
{
    uint64_t result = 0;
    for (auto &operation : operations)
    {
        result += operation.second.value();
    }
    return result;
}

void AddParentheses(Operation &operation)
{
    size_t i = operation.first.find("*");
    while (i != std::string::npos)
    {
        operation.first.insert(i + 2, "(");
        auto match = FindMatchingParenthesis(operation.first, i + 2);
        if (match != std::string::npos)
            operation.first.insert(match, ")");
        else
            operation.first.push_back(')');
        i = operation.first.find("*", i + 1);
    }
}

void AddParentheses(Operations &operations)
{
    for (auto &operation : operations)
    {
        AddParentheses(operation);
    }
}

//Main function
int main()
{

    Operations operations = ReadOperations("C:\\Users\\alex1\\git\\AdventOfCode\\day18\\input.txt");
    Solve(operations);
    auto result = SumSolutions(operations);

    AddParentheses(operations);
    Solve(operations);
    auto result2 = SumSolutions(operations);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}