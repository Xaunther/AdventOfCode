//To solve day 12 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define pi acos(-1)
//3 types of instructions
enum class ActionType
{
    N = 90,
    S = 270,
    E = 360,
    W = 180,
    L = 1,
    R = 3,
    F = 0,
};

ActionType CharToActionType(char const s)
{
    switch (s)
    {
    case 'N':
        return ActionType::N;
        break;
    case 'S':
        return ActionType::S;
        break;
    case 'E':
        return ActionType::E;
        break;
    case 'W':
        return ActionType::W;
        break;
    case 'L':
        return ActionType::L;
        break;
    case 'R':
        return ActionType::R;
        break;
    case 'F':
        return ActionType::F;
        break;
    default:
        return ActionType::F;
        break;
    }
}

using Action = std::pair<ActionType, int>;
using ActionList = std::vector<Action>;

class Ship
{
private:
    std::pair<int, int> m_coordinates;
    int m_direction;
    std::pair<int, int> m_waypoint;

public:
    Ship() : m_coordinates({0, 0}), m_direction(0), m_waypoint{10, 1} {}
    void Perform(ActionList const &actions, bool const use_waypoint);
    void Perform(Action const &action, bool const use_waypoint);
    void Rotate(int const degrees, bool const use_waypoint);
    void Propel(int const distance, bool const use_waypoint);
    void Propel(int const distance, int const direction, bool const use_waypoint);
    unsigned int ManhattanDistance() const { return abs(m_coordinates.first) + abs(m_coordinates.second); }
};

void Ship::Perform(ActionList const &actions, bool const use_waypoint)
{
    for (auto action : actions)
    {
        Perform(action, use_waypoint);
        //std::cout << m_coordinates.first << ", " << m_coordinates.second << ", " << m_direction << std::endl;
    }
}
void Ship::Perform(Action const &action, bool const use_waypoint)
{
    if (action.first == ActionType::F) //Forward
        Propel(action.second, use_waypoint);
    else if ((int)action.first % 90 == 0) //Propelling
        Propel(action.second, (int)action.first, use_waypoint);
    else //Rotating
        Rotate(action.second * (int)action.first, use_waypoint);
}

void Ship::Rotate(int const degrees, bool const use_waypoint)
{
    if (!use_waypoint) //Rotate ship
        m_direction = (m_direction + degrees) % 360;
    else //Rotate waypoint
    {
        std::pair<int, int> _temp;
        _temp.first = m_waypoint.first * int(cos(double(degrees) / 360.0 * 2 * pi)) - m_waypoint.second * int(sin(double(degrees) / 360.0 * 2 * pi));
        _temp.second = m_waypoint.second * int(cos(double(degrees) / 360.0 * 2 * pi)) + m_waypoint.first * int(sin(double(degrees) / 360.0 * 2 * pi));
        m_waypoint = _temp;
    }
}

void Ship::Propel(int const distance, bool const use_waypoint)
{
    if (!use_waypoint) //Propel ship
    {
        m_coordinates.first += distance * int(cos(double(m_direction) / 360.0 * 2 * pi));
        m_coordinates.second += distance * int(sin(double(m_direction) / 360.0 * 2 * pi));
    }
    else //Propel to waypoint
    {
        m_coordinates.first += distance * m_waypoint.first;
        m_coordinates.second += distance * m_waypoint.second;
    }
}

void Ship::Propel(int const distance, int const direction, bool const use_waypoint)
{
    if (!use_waypoint) //Propel ship
    {
        m_coordinates.first += distance * int(cos(double(direction) / 360.0 * 2 * pi));
        m_coordinates.second += distance * int(sin(double(direction) / 360.0 * 2 * pi));
    }
    else //Move waypoint
    {
        m_waypoint.first += distance * int(cos(double(direction) / 360.0 * 2 * pi));
        m_waypoint.second += distance * int(sin(double(direction) / 360.0 * 2 * pi));
    }
}

ActionList ReadActions(std::string filename)
{
    ActionList actions;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //Reading is quite easy
            std::string input_thing;
            infile >> input_thing;
            actions.push_back({CharToActionType(input_thing[0]), stoi(input_thing.substr(1))});
        }
    }
    return actions;
}

//Main function
int main()
{
    Ship ship, ship2;
    ActionList actions = ReadActions("C:\\Users\\alex1\\git\\AdventOfCode\\day12\\input.txt");
    ship.Perform(actions, false);
    ship2.Perform(actions, true);

    unsigned int result = ship.ManhattanDistance();
    unsigned int result2 = ship2.ManhattanDistance();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}