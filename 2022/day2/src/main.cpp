#include <iostream>
#include <list>
#include <numeric>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CMatch.h"
#include "CFixedMatch.h"

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
	const auto& matches = CreateUnorderedContainerFromFile<std::list<CMatch>>( aFileName );
	return std::accumulate( matches.cbegin(), matches.cend(), static_cast< unsigned long >( 0 ), []( const auto& aResult, const auto& aMatch )
		{ return aResult + aMatch.MyScore(); } );
}

unsigned long Part2( const std::string& aFileName )
{
	const auto& matches = CreateUnorderedContainerFromFile<std::list<CFixedMatch>>( aFileName );
	return std::accumulate( matches.cbegin(), matches.cend(), static_cast< unsigned long >( 0 ), []( const auto& aResult, const auto& aMatch )
		{ return aResult + aMatch.MyScore(); } );
}

}