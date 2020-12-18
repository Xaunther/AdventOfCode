//To solve day 17 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <array>

//Bounds of our 3D space, it marks where the outermost cubes might possibly be
using Bounds = std::array<std::pair<int32_t, int32_t>, 3>;
//Cubes: coordinates and state
using Cube = std::pair<std::array<int32_t, 3>, bool>;
using Cubes = std::map<std::array<int32_t, 3>, bool>;
//Space: Composed by all cubes and the bounds of it. Anything outside is also inactive
using Space3D = std::pair<Bounds, Cubes>;

Space3D ReadSpace3D(std::string const &filename)
{
    std::ifstream infile;
    Space3D space3D;
    infile.open(filename.c_str());
    std::string input_line;
    if (!infile.is_open())
        return space3D;
    //The input is always z = 0, just read boye
    std::getline(infile, input_line);

    //With this we can bound x and z, and initialize y
    space3D.first[0] = {-1, int32_t(input_line.size())};
    space3D.first[1] = {-1, 0}; //Bit dummy
    space3D.first[2] = {-1, 1};
    while (input_line != "")
    {

        for (auto i = 0; i < input_line.size(); i++)
        {
            if (input_line[i] == '.') //Inactive
                space3D.second[{i, space3D.first[1].second, 0}] = false;
            else //Active
                space3D.second[{i, space3D.first[1].second, 0}] = true;
        }
        //Increase Y-axis
        space3D.first[1].second++;
        //Go on
        input_line = "";
        std::getline(infile, input_line);
    }
    return space3D;
}

void ExtendBounds(Bounds &bounds)
{
    for (auto &bound : bounds)
    {
        bound.first--;
        bound.second++;
    }
}

uint32_t GetActiveNeighbours(Space3D &space3D, std::array<int32_t, 3> const &point)
{
    uint32_t result = 0;
    for (auto x_i = point[0] - 1; x_i <= point[0] + 1; x_i++)
    {
        for (auto y_i = point[1] - 1; y_i <= point[1] + 1; y_i++)
        {
            for (auto z_i = point[2] - 1; z_i <= point[2] + 1; z_i++)
            {
                if (x_i != point[0] || y_i != point[1] || z_i != point[2])
                    result += (int)space3D.second[{x_i, y_i, z_i}];
            }
        }
    }
    return result;
}

bool HasToChange(Space3D &space3D, std::array<int32_t, 3> const &point)
{
    auto active_neighbours = GetActiveNeighbours(space3D, point);
    if (space3D.second[point]) //If active
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

//Do a cycle according to the given rules
void DoCycle(Space3D &space3D)
{
    //In a cycle, we first extends bounds by abs(1) on each side
    ExtendBounds(space3D.first);

    Cubes new_cubes = space3D.second;

    //Now loop over 3D. No need to be looking at the bounds
    for (auto x_i = space3D.first[0].first + 1; x_i < space3D.first[0].second; x_i++)
    {
        for (auto y_i = space3D.first[1].first + 1; y_i < space3D.first[1].second; y_i++)
        {
            for (auto z_i = space3D.first[2].first + 1; z_i < space3D.first[2].second; z_i++)
            {
                if (HasToChange(space3D, {x_i, y_i, z_i}))
                {
                    new_cubes[{x_i, y_i, z_i}] = !space3D.second[{x_i, y_i, z_i}];
                }
            }
        }
    }
    space3D.second = new_cubes;
}

//Do N cycles according to the given rules
void DoNCycles(Space3D &space3D, uint32_t const &N)
{
    for (uint32_t i = 0; i < N; i++) //Do a cycle N times
    {
        DoCycle(space3D);
    }
}

uint64_t CountActive(Space3D const &space3D)
{
    uint64_t result = 0;
    //Now loop all map elements
    for (auto cube : space3D.second)
    {
        //std::cout << "[" << cube.first[0] << "," << cube.first[1] << "," << cube.first[2] << "]: " << cube.second << std::endl;
        result += (int)cube.second;
    }
    return result;
}

//Main function
int main()
{

    auto space3D = ReadSpace3D("C:\\Users\\alex1\\git\\AdventOfCode\\day17\\input.txt");
    DoNCycles(space3D, 6);
    auto result = CountActive(space3D);
    std::cout << "Result: " << result << std::endl;
    /*
    auto instructions = ReadInstructions("C:\\Users\\alex1\\git\\AdventOfCode\\day14\\input.txt");
    auto addresses = ProcessInstructions(instructions);
    auto result = SumMap(addresses);

    auto addresses2 = ProcessInstructions2(instructions);
    auto result2 = SumMap(addresses2);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    */
    return 0;
}