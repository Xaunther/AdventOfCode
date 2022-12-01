#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "CElf.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
unsigned long Part1( const std::string& aFileName );
unsigned long Part2( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	std::cout << "Part 2 example: " << Part2( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

unsigned long Part1( const std::string& aFileName )
{
	const auto& elves = CreateUnorderedContainerFromFile<std::list<CElf>>( aFileName );
	return ( *std::max_element( elves.cbegin(), elves.cend(), []( const CElf& aLHS, const CElf& aRHS )
		{ return aLHS.GetCalories() < aRHS.GetCalories(); } ) ).GetCalories();
}

unsigned long Part2( const std::string& aFileName )
{
	auto elves = CreateUnorderedContainerFromFile<std::vector<CElf>>( aFileName );
	std::nth_element( elves.begin(), elves.begin() + 3, elves.end(), []( const CElf& aLHS, const CElf& aRHS )
		{ return aLHS.GetCalories() >= aRHS.GetCalories(); } );
	return elves[ 0 ].GetCalories() + elves[ 1 ].GetCalories() + elves[ 2 ].GetCalories();
}

}