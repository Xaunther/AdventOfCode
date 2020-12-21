//To solve day 20 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>

using Allergens = std::list<std::pair<std::vector<std::string>, std::vector<std::string>>>;
using AllergenMap = std::map<std::string, std::vector<std::string>>;

std::vector<std::string> SplitString(std::string const &s, std::string const pattern)
{
    if (s.find(pattern) == std::string::npos)
        return {s};

    std::vector<std::string> s_list;
    size_t i = 0;
    while (s.find(pattern, i) != std::string::npos)
    {
        s_list.push_back(s.substr(i, s.find(pattern, i) - i));
        i = s.find(pattern, i) + pattern.size();
    }
    //Add last
    s_list.push_back(s.substr(i));
    return s_list;
}

Allergens ReadAllergens(std::string const &filename)
{
    Allergens allergens;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return allergens;

    std::string input_thing;
    //Read line by line
    std::getline(infile, input_thing);
    while (input_thing != "")
    {
        //Split ingredients and allergens
        auto parts = SplitString(input_thing, " (contains ");
        //Split ingredients
        auto ingredients = SplitString(parts[0], " ");
        //Split allergens
        auto allergies = SplitString(parts[1].substr(0, parts[1].size() - 1), ", ");
        //Add to list
        allergens.push_back({ingredients, allergies});
        input_thing = "";
        std::getline(infile, input_thing);
    }
    infile.close();
    return allergens;
}

std::vector<std::string> KeepCommon(std::vector<std::string> const &v1, std::vector<std::string> const &v2)
{
    std::vector<std::string> common_v;
    for (auto e1 : v1)
    {
        for (auto e2 : v2)
        {
            if (e1 == e2)
                common_v.push_back(e1);
        }
    }
    return common_v;
}

void Print(AllergenMap const &allergenmap)
{
    for (auto a : allergenmap)
    {
        std::cout << a.first << ": ";
        for (auto b : a.second)
        {

            std::cout << b << ", ";
        }
        std::cout << std::endl;
    }
}

void Clean(AllergenMap &allergenmap, std::string const &search_str)
{
    for (auto &allergen_search : allergenmap)
    {
        if (allergen_search.second.size() > 1)
        {
            for (auto v = allergen_search.second.begin(); v != allergen_search.second.end(); ++v)
            {
                if (*v == search_str)
                {
                    allergen_search.second.erase(v);
                    break;
                }
            }
        }
    }
}

void Simplify(AllergenMap &allergenmap)
{
    uint64_t counter;
    do
    {
        for (auto allergen : allergenmap)
        {
            if (allergen.second.size() == 1) //Time to clean!
            {
                Clean(allergenmap, allergen.second[0]);
            }
        }
        counter = 0;
        for (auto allergen : allergenmap)
        {
            counter += allergen.second.size();
        }
    } while (counter > allergenmap.size());
}

AllergenMap DetermineAllergens(Allergens const &allergens)
{
    AllergenMap allergenmap;
    //We loop over all allergens in the list and add them to map
    for (auto allergen_v : allergens)
    {
        for (auto allergen : allergen_v.second)
        {
            //If this allergen is new just add it, otherwise only keep common ingredients!
            if (allergenmap.find(allergen) == allergenmap.end())
                allergenmap[allergen] = allergen_v.first;
            else
                allergenmap[allergen] = KeepCommon(allergenmap[allergen], allergen_v.first);
        }
    }
    //After retaining the common ingredients, clean our map until we have 1 entry for each allergen
    Simplify(allergenmap);
    return allergenmap;
}

std::list<std::string> GetIngredients(Allergens const &allergens)
{
    std::list<std::string> ingredients;
    for (auto &allergen : allergens)
    {
        for (auto &ingredient : allergen.first)
        {
            ingredients.push_back(ingredient);
        }
    }
    ingredients.sort();
    ingredients.unique();
    return ingredients;
}

bool IsFoundInMap(AllergenMap const &allergenmap, std::string const &ingredient)
{
    for (auto &allergen : allergenmap)
    {
        for (auto &a : allergen.second)
        {
            if (a == ingredient)
                return true;
        }
    }
    return false;
}

std::list<std::string> GetGoodIngredients(AllergenMap const &allergenmap, std::list<std::string> const &ingredients)
{
    std::list<std::string> goodingredients;
    for (auto &ingredient : ingredients)
    {
        if (!IsFoundInMap(allergenmap, ingredient))
            goodingredients.push_back(ingredient);
    }
    return goodingredients;
}

size_t CountAppearances(std::string const &ingredient, Allergens const &allergens)
{
    size_t result = 0;
    for (auto &allergen : allergens)
    {
        for (auto &a : allergen.first)
        {
            if (a == ingredient)
                result++;
        }
    }
    return result;
}

size_t CountAppearances(std::list<std::string> const &ingredients, Allergens const &allergens)
{
    size_t result = 0;
    for (auto &ingredient : ingredients)
        result += CountAppearances(ingredient, allergens);
    return result;
}

int main()
{
    //Let's read and get list of allergens
    auto allergens = ReadAllergens("C:\\Users\\alex1\\git\\AdventOfCode\\day21\\input.txt");
    //Time to collapse the raw list into a map
    auto allergenmap = DetermineAllergens(allergens);
    //Let's get also a list with all the ingredients
    auto ingredients = GetIngredients(allergens);
    //And now a list of ingredients without known allergens, and also the bad ones
    auto goodingredients = GetGoodIngredients(allergenmap, ingredients);
    //Finally, count all appearances of ingredients in the original list
    auto result = CountAppearances(goodingredients, allergens);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: ";
    for (auto &allergen : allergenmap)
    {
        std::cout << allergen.second[0] << ",";
    }
    return 0;
}