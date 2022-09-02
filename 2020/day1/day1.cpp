//To solve day 1 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

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

//Find pair of numbers that adds to a certain number
template <typename T>
std::optional<std::pair<T, T>> FindPairThatSums(std::vector<T> const &v, T const sum, typename std::vector<T>::const_iterator start)
{
    //Do the search
    for (auto v_i = start; v_i != v.end(); ++v_i)
    {
        for (auto v_j = v_i + 1; v_j != v.end(); ++v_j)
        {
            if (*v_i + *v_j == sum)
            {
                return std::pair<T, T>(*v_i, *v_j);
            }
        }
    }
    return {};
}

//Find pair of numbers that adds to a certain number
template <typename T>
std::optional<std::pair<T, T>> FindPairThatSums(std::vector<T> const &v, T const sum)
{
    return FindPairThatSums(v, sum, v.begin());
}

//Find N-tuple of numbers that add to a certain number
template <typename T>
std::optional<std::vector<T>> FindNTupleThatSums(std::vector<T> const &v, T const sum, int N, typename std::vector<T>::const_iterator start)
{
    //If we are finding a pair, use the pair finding function
    if (N == 2)
    {
        auto lastpair = FindPairThatSums(v, sum, start);
        if (!lastpair.has_value())
            return {};
        else
            return std::vector<T>{lastpair.value().first, lastpair.value().second};
    }
    //Otherwise, keep rolling
    for (auto &v_i = start; v_i != v.end(); ++v_i)
    {
        auto result = FindNTupleThatSums(v, sum - *v_i, N - 1, v_i + 1);
        if (result.has_value())
        {
            result.value().insert(result.value().begin(), *v_i);
            return result;
        }
    }
    return {};
}
//Find N-tuple of numbers that add to a certain number
template <typename T>
std::optional<std::vector<T>> FindNTupleThatSums(std::vector<T> const &v, T const sum, int N)
{
    return FindNTupleThatSums(v, sum, N, v.begin());
}

//Main function
int main()
{
    std::vector<int> values = FileToVector<int>("C:\\Users\\alex1\\git\\AdventOfCode\\day1\\input.txt");
    std::optional<std::pair<int, int>> value_pair = FindPairThatSums(values, 2020);
    std::optional<std::vector<int>> value_triplet = FindNTupleThatSums(values, 2020, 3);
    std::cout << "Result: " << value_pair.value().first << " * " << value_pair.value().second << " = " << value_pair.value().first * value_pair.value().second << std::endl;
    std::cout << "Result: " << value_triplet.value()[0] << " * " << value_triplet.value()[1] << " * " << value_triplet.value()[2] << " = " << value_triplet.value()[0] * value_triplet.value()[1] * value_triplet.value()[2]<< std::endl;

    return 0;
}