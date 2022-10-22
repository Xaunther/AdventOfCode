#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CBurrow.h"
#include "CMultiGameState.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string INPUT2_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input2.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";
static const std::string EXAMPLE2_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example2.txt";

std::size_t Part1( const std::string& aFileName );
std::size_t Part2( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	std::cout << "Part 2 example: " << Part2( EXAMPLE2_FILE_NAME ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT2_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

std::size_t Part1( const std::string& aFileName )
{
	const auto& burrow = CreateFromFile<CBurrow>( aFileName );
	auto multiGameState = CreateFromFile<CMultiGameState>( aFileName );
	multiGameState.Play( burrow );
	return multiGameState.GetMinimumEnergy().value_or( 0 );
}

std::size_t Part2( const std::string& aFileName )
{
	const auto& burrow = CreateFromFile<CBurrow>( aFileName );
	auto multiGameState = CreateFromFile<CMultiGameState>( aFileName );
	multiGameState.Play( burrow );
	return multiGameState.GetMinimumEnergy().value_or( 0 );
}

}