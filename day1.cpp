//To solve day 1 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Read into vector
template <typename T>
std::vector<T> FileToVector(std::string filename)
{
    std::vector<T> readlist;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            T input_thing;
            infile >> input_thing;
            readlist.push_back(input_thing);
        }
    }
    return readlist;
}

//Find pair of idnexes that adds to a certain number
template <typename T>
std::pair<T, T> FindPairThatSums(std::vector<T> &v, T sum)
{
    for (auto &v_i = v.begin(); v_i != v.end(); ++v_i)
    {
        for (auto &v_j = v_i + 1; v_j != v.end(); ++v_j)
        {
            if (*v_i + *v_j == sum)
            {
                return std::pair<T, T>(*v_i, *v_j);
            }
        }
    }
    return {};
}

//Main function
int main()
{
    std::vector<int> values = FileToVector<int>("C:\\Users\\alex1\\git\\AdventOfCode\\day1\\input.txt");
    std::pair<int, int> value_pair = FindPairThatSums(values, 2020);
    std::cout << "Result: " << value_pair.first << " * " << value_pair.second << " = " << value_pair.first * value_pair.second << std::endl;
    return 0;
}