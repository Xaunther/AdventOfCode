//To solve day 10 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <optional>
#include <vector>
#include <iterator>
#include <algorithm>

void PrintVector(std::vector<unsigned int> const &v)
{
    for (auto vv : v)
        std::cout << vv << std::endl;
    std::cout << "--" << std::endl;
}

std::list<unsigned int> ReadJolts(std::string filename)
{
    std::list<unsigned int> jolts;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //Reading is quite easy
            unsigned int input_number;
            infile >> input_number;
            jolts.push_back(input_number);
        }
    }
    jolts.sort();
    return jolts;
}

unsigned int GetNJumpsOf(std::list<unsigned int> const &jolts, unsigned int const &jump)
{
    unsigned int previous = 0;
    unsigned int counter = 0;
    for (auto jolt : jolts)
    {
        if (jolt - previous == jump)
            counter++;
        previous = jolt;
    }
    return counter;
}

std::vector<std::pair<unsigned int, unsigned int>> GetSegments(std::list<unsigned int> const &jolts)
{
    std::vector<std::pair<unsigned int, unsigned int>> segments;
    std::pair<unsigned int, unsigned int> segment;
    unsigned int i = 0;
    for (auto &jolt : jolts)
    {
        if (i == 0)
            segment.first = i;
        else if (i == jolts.size() - 1)
        {
            segment.second = i;
            segments.push_back(segment);
        }
        else if (*std::next(jolts.begin(), i - 1) == jolt - 3 || *std::next(jolts.begin(), i + 1) == jolt + 3)
        {
            segment.second = i;
            segments.push_back(segment);
            segment.first = i;
        }
        else if (*std::next(jolts.begin(), i - 1) == jolt - 2 && *std::next(jolts.begin(), i + 1) == jolt + 2)
        {
            segment.second = i;
            segments.push_back(segment);
            segment.first = i;
        }
        i++;
    }
    return segments;
}

bool IsValid(std::vector<unsigned int> const &jolt_segment)
{
    unsigned int previous = jolt_segment[0];
    for (auto element : jolt_segment)
    {
        if (element - previous > 3)
            return false;
        previous = element;
    }
    return true;
}

unsigned long long GetNCombinations(std::vector<unsigned int> const &jolt_segment, unsigned int start = 1)
{
    unsigned long long result = 0;
    //Loop from start and try removing, if correct, add and try removing more (recursive). First and last elements are not removable
    for (unsigned int i = start; i < jolt_segment.size() - 1; i++)
    {
        std::vector<unsigned int> jolt_segment_cut;
        for (auto element : jolt_segment)
        {
            if (element != jolt_segment[i])
                jolt_segment_cut.push_back(element);
        }
        if (IsValid(jolt_segment_cut))
        {
            //PrintVector(jolt_segment_cut);
            result++;
            result += GetNCombinations(jolt_segment_cut, i);
            //std::cout << "--" << result << "--" << std::endl;
        }
    }
    return result;
}
unsigned long long GetNCombinations(std::list<unsigned int> const &jolts, std::vector<std::pair<unsigned int, unsigned int>> const &segments)
{
    unsigned long long result = 1;
    //We loop over all segments and multiply
    for (auto segment : segments)
    {
        //std::cout << segment.first << ", " << segment.second << std::endl;
        std::vector<unsigned int> jolt_segment;
        for (unsigned int i = segment.first; i <= segment.second; i++)
            jolt_segment.push_back(*(std::next(jolts.begin(), i)));
        result = result * (GetNCombinations(jolt_segment) + 1);
    }
    return result;
}

//Main function
int main()
{
    std::list<unsigned int> jolts = ReadJolts("C:\\Users\\alex1\\git\\AdventOfCode\\day10\\input.txt");
    unsigned int result = GetNJumpsOf(jolts, 1) * (GetNJumpsOf(jolts, 3) + 1);
    //The idea here is to find those numbers which cannot be removed (either next OR previous jumps 3 or both next AND previous jump 2)
    jolts.push_front(0);
    std::vector<std::pair<unsigned int, unsigned int>> segments = GetSegments(jolts);
    //After that, each smaller segment is force-brutted to find their iterations
    unsigned long long result2 = GetNCombinations(jolts, segments);
    //std::pair<unsigned int, unsigned int> result2 = FindContiguousSetAdding(numbers, result.value());

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}