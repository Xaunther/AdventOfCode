#include <iostream>
#include <string>
#include <numeric>
#include <functional>

#include "year.h"
#include "day.h"

#include "CDisplay.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

size_t Part1( const std::string& aFileName );
size_t Part2( const std::string& aFileName );

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

size_t Part1( const std::string& aFileName )
{
	const auto& display = CreateListFromFile<CDisplay>( aFileName );
	return std::accumulate( display.cbegin(), display.cend(), static_cast< size_t >( 0 ),
		[]( const auto& aResult, const auto& aDisplay ) { return aResult + aDisplay.CountUniqueOutputs(); } );
}

size_t Part2( const std::string& aFileName )
{
	const auto& display = CreateListFromFile<CDisplay>( aFileName );
	return std::accumulate( display.cbegin(), display.cend(), static_cast< size_t >( 0 ),
		[]( const auto& aResult, const auto& aDisplay ) { return aResult + aDisplay.SolveOutput(); } );
}

}