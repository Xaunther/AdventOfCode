//To solve day 20 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using Cups = std::list<size_t>;

void Print(Cups const &cups)
{
    for (auto cup : cups)
        std::cout << "(" << cup << ")";
    std::cout << std::endl;
}

Cups StringToCups(std::string const &str)
{
    Cups cups;
    for (auto c : str)
        cups.push_back(c - 48);
    return cups;
}

Cups ReadCups(std::string const &filename)
{
    Cups cups;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return cups;

    // Just one line, transform string into digits
    std::string input_thing;
    std::getline(infile, input_thing);
    cups = StringToCups(input_thing);
    infile.close();
    return cups;
}

void Fill(Cups &cups, size_t const size)
{
    while (cups.size() < size)
        cups.push_back(cups.size() + 1);
}

Cups ReadCups2(std::string const &filename, size_t const size)
{
    Cups cups;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return cups;

    // Just one line, transform string into digits
    std::string input_thing;
    std::getline(infile, input_thing);
    cups = StringToCups(input_thing);
    infile.close();
    Fill(cups, size);
    return cups;
}

Cups::iterator FindNextCup(Cups &cups, uint32_t const N_cupsmoved)
{
    size_t search_index = *cups.begin() - 1;
    if (search_index == 0)
        search_index = uint32_t(cups.size()) + N_cupsmoved;
    //We loop until we find a match. There's always a match
    while (true)
    {
        auto cup = std::find(cups.begin(), cups.end(), search_index);
        if (cup != cups.end())
        {
            std::advance(cup, 1);
            return cup;
        }

        search_index--;
        if (search_index == 0)
            search_index = uint32_t(cups.size()) + N_cupsmoved;
    }
}

void PlayCups(Cups &cups, uint32_t const N_cupsmoved)
{
    //Play 1 round of cups
    //Our current cup is ALWAYS the first. We are going to move N_cupsmoved cups
    //Extract these N cups
    Cups::iterator begin_it = cups.begin();
    Cups::iterator target_it = cups.begin();
    std::advance(begin_it, 1);
    std::advance(target_it, N_cupsmoved + 1);

    Cups extracted_cups;
    extracted_cups.splice(extracted_cups.begin(), cups, begin_it, target_it);

    //Now look for cup where these N will be inserted
    target_it = FindNextCup(cups, N_cupsmoved);
    //Reinsert at that place
    cups.splice(target_it, extracted_cups, extracted_cups.begin(), extracted_cups.end());

    //Last, put first element to last position
    target_it = cups.begin();
    std::advance(target_it, 1);
    std::rotate(cups.begin(), target_it, cups.end());
    return;
}

void PlayCups(Cups &cups, uint32_t const N_rounds, uint32_t const N_cupsmoved)
{
    //Play N rounds
    for (uint32_t i = 0; i < N_rounds; i++)
    {
        if (i % 1000 == 0)
            std::cout << i << std::endl;
        PlayCups(cups, N_cupsmoved);
    }
}

void Reorder(Cups &cups, uint32_t number)
{
    //Find the 1 in the vector
    Cups::iterator target_it;
    for (target_it = cups.begin(); *target_it != number; ++target_it)
    {
    }

    //Rotate
    std::rotate(cups.begin(), target_it, cups.end());
}

uint64_t GetProduct(Cups const &cups, size_t const N)
{
    uint64_t result = 1;
    Cups::const_iterator it = cups.begin();
    for (int i = 0; i < N; i++)
    {
        std::advance(it, 1);
        result = result * (*it);
    }
    return result;
}

int main()
{
    //Read the cups
    auto cups = ReadCups("C:\\Users\\alex1\\git\\AdventOfCode\\day23\\input.txt");
    //Play 100 rounds
    PlayCups(cups, 100, 3);
    //Reorder putting 1 in first place
    Reorder(cups, 1);

    std::cout << "Result: ";
    Print(cups);

    //Part two, read the cups in a different manner and replay the game
    cups = ReadCups2("C:\\Users\\alex1\\git\\AdventOfCode\\day23\\input.txt", 1000000);
    //Now play 10^7 moves
    PlayCups(cups, 10000000, 3);
    Reorder(cups, 1);
    auto result2 = GetProduct(cups, 2);
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}