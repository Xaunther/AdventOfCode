//To solve day 17 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <array>

//Bounds of our 3D space, it marks where the outermost cubes might possibly be
using Bounds = std::vector<std::pair<int32_t, int32_t>>;
//Cubes: coordinates and state
using Cube = std::pair<std::vector<int32_t>, bool>;
using Cubes = std::map<std::vector<int32_t>, bool>;
//Space: Composed by all cubes and the bounds of it. Anything outside is also inactive
using Space = std::pair<Bounds, Cubes>;

Space ReadSpace(std::string const &filename, uint32_t const dimensions = 3)
{
    std::ifstream infile;
    Space space;
    infile.open(filename.c_str());
    std::string input_line;
    if (!infile.is_open())
        return space;
    //The input is always z = 0, just read boye
    std::getline(infile, input_line);
    //With this we can bound x and z, and initialize y
    space.first.push_back({-1, int32_t(input_line.size())});
    space.first.push_back({-1, 0}); //Bit dummy
    for (uint8_t i = 2; i < dimensions; i++)
        space.first.push_back({-1, 1});
    while (input_line != "")
    {

        for (auto i = 0; i < input_line.size(); i++)
        {
            std::vector<int32_t> point;
            point.push_back(i);
            point.push_back(space.first[1].second);
            for (uint32_t j = 2; j < dimensions; j++)
                point.push_back(0);

            if (input_line[i] == '.') //Inactive
                space.second[point] = false;
            else //Active
            {
                space.second[point] = true;
            }
        }
        //Increase Y-axis
        space.first[1].second++;
        //Go on
        input_line = "";
        std::getline(infile, input_line);
    }
    return space;
}

void ExtendBounds(Bounds &bounds)
{
    for (auto &bound : bounds)
    {
        bound.first--;
        bound.second++;
    }
}

uint32_t GetActiveNeighbours(Space &space, std::vector<int32_t> const &point, std::vector<int32_t> neighbour = {})
{
    if (neighbour == point)
        return 0;
    uint32_t result = 0;
    if (neighbour.size() >= space.first.size())
        return (int)space.second[neighbour];

    for (auto x_i = point[neighbour.size()] - 1; x_i <= point[neighbour.size()] + 1; x_i++)
    {
        neighbour.push_back(x_i);
        result += GetActiveNeighbours(space, point, neighbour);
        neighbour.pop_back();
    }

    return result;
}

bool HasToChange(Space &space, std::vector<int32_t> const &point)
{
    auto active_neighbours = GetActiveNeighbours(space, point);
    if (space.second[point]) //If active
    {
        if (active_neighbours != 2 && active_neighbours != 3)
            return true;
    }
    else //If inactive
    {
        if (active_neighbours == 3)
            return true;
    }
    return false;
}

void Loop(Cubes &new_cubes, Space &space, std::vector<int32_t> point = {})
{
    if (point.size() >= space.first.size())
    {
        if (HasToChange(space, point))
            new_cubes[point] = !space.second[point];
    }
    else
    {
        for (auto x_i = space.first[point.size()].first + 1; x_i < space.first[point.size()].second; x_i++)
        {
            point.push_back(x_i);
            Loop(new_cubes, space, point);
            point.pop_back();
        }
    }
}

//Do a cycle according to the given rules
void DoCycle(Space &space)
{
    //In a cycle, we first extends bounds by abs(1) on each side
    ExtendBounds(space.first);

    Cubes new_cubes = space.second;

    //Now loop over 3D. No need to be looking at the bounds
    Loop(new_cubes, space);
    space.second = new_cubes;
}

//Do N cycles according to the given rules
void DoNCycles(Space &space, uint32_t const &N)
{
    for (uint32_t i = 0; i < N; i++) //Do a cycle N times
    {
        DoCycle(space);
    }
}

uint64_t CountActive(Space const &space)
{
    uint64_t result = 0;
    //Now loop all map elements
    for (auto cube : space.second)
    {
        result += (int)cube.second;
    }

    return result;
}

//Main function
int main()
{

    auto space3 = ReadSpace("C:\\Users\\alex1\\git\\AdventOfCode\\day17\\input.txt", 3);
    auto space4 = ReadSpace("C:\\Users\\alex1\\git\\AdventOfCode\\day17\\input.txt", 4);

    DoNCycles(space3, 6);
    DoNCycles(space4, 6);

    auto result = CountActive(space3);
    auto result2 = CountActive(space4);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}