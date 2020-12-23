//To solve day 20 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>

using Combat = std::pair<std::vector<uint32_t>, std::vector<uint32_t>>;

Combat ReadCombat(std::string const &filename)
{
    Combat combat;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return combat;

    std::string input_thing;
    //Read line by line player 1
    std::getline(infile, input_thing);
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        //Split ingredients and allergens
        combat.first.push_back(std::stoi(input_thing));
        input_thing = "";
        std::getline(infile, input_thing);
    }
    //Player two;
    std::getline(infile, input_thing);
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        //Split ingredients and allergens
        combat.second.push_back(std::stoi(input_thing));
        input_thing = "";
        std::getline(infile, input_thing);
    }
    infile.close();
    return combat;
}

void Play(Combat &combat)
{
    //Go until someone runs out of cards
    while (combat.first.size() > 0 && combat.second.size() > 0)
    {
        if (combat.first[0] > combat.second[0]) //Player 1 wins
        {
            combat.first.push_back(combat.first[0]);
            combat.first.push_back(combat.second[0]);
        }
        else
        {
            combat.second.push_back(combat.second[0]);
            combat.second.push_back(combat.first[0]);
        }
        //Erase top cards from top
        combat.first.erase(combat.first.begin());
        combat.second.erase(combat.second.begin());
    }
}

uint64_t CountPoints(Combat const &combat)
{
    uint64_t result = 0;
    uint32_t i = 1;
    if (combat.second.size() == 0) //P1 won
    {
        for (auto card = combat.first.rbegin(); card != combat.first.rend(); ++card)
        {
            result += *card * i;
            i++;
        }
    }
    else //P2 won
    {
        for (auto card = combat.second.rbegin(); card != combat.second.rend(); ++card)
        {
            result += *card * i;
            i++;
        }
    }
    return result;
}

bool IsFound(Combat const &combat, std::list<Combat> const &combat_history)
{
    for (auto &combat_h : combat_history)
    {
        if (combat_h == combat)
            return true;
    }
    return false;
}

Combat CopyWithTopRemoved(Combat const &combat, std::pair<uint32_t, uint32_t> const N)
{
    Combat removed_combat;
    for (uint32_t i = 1; i <= N.first; i++)
        removed_combat.first.push_back(combat.first[i]);
    for (uint32_t i = 1; i <= N.second; i++)
        removed_combat.second.push_back(combat.second[i]);
    return removed_combat;
}

//Returns true if Player 1 wins, false if player 2 wins
bool PlayRecursive(Combat &combat)
{
    //Define history of hands, halt if we reached a loop
    std::list<Combat> combat_history;
    //Go until someone runs out of cards, in principle
    while (combat.first.size() > 0 && combat.second.size() > 0)
    {
        //Check if this hand is in history. If it is, player 1 wins
        if (IsFound(combat, combat_history))
            return true;
        //Add this hand to history
        combat_history.push_back(combat);
        bool p1_wins;
        //Draw cards, if the numbers drawn are both below the size of their respective decks, play a recursive game
        if (combat.first[0] < combat.first.size() && combat.second[0] < combat.second.size())
        {
            Combat rec_combat = CopyWithTopRemoved(combat, {combat.first[0], combat.second[0]});
            p1_wins = PlayRecursive(rec_combat);
        }
        else //Otherwise, play normal hand and see who wins
        {
            if (combat.first[0] > combat.second[0])
                p1_wins = true;
            else
                p1_wins = false;
        }
        //We determined who won this hand, now put the cards on the back
        if (p1_wins) //If p1 wins
        {
            combat.first.push_back(combat.first[0]);
            combat.first.push_back(combat.second[0]);
        }
        else //If p2 wins
        {
            combat.second.push_back(combat.second[0]);
            combat.second.push_back(combat.first[0]);
        }
        //Remove top cards
        combat.first.erase(combat.first.begin());
        combat.second.erase(combat.second.begin());
    }
    //When someone ran out of cards, let's see who won
    if (combat.second.size() == 0)
        return true;
    else
        return false;
}

int main()
{
    //Let's read the cards dealt
    auto combat_raw = ReadCombat("C:\\Users\\alex1\\git\\AdventOfCode\\day22\\input.txt");
    //Play the game! And count the points
    Combat combat = combat_raw;
    Play(combat);
    auto result = CountPoints(combat);
    //Play the recursive game! And count the points
    combat = combat_raw;
    PlayRecursive(combat);
    auto result2 = CountPoints(combat);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}