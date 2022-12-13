#include <iostream>
#include <ranges>
#include <vector>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CDistressSignal.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
unsigned int Part1( const std::string& aFileName );
unsigned int Part2( const std::string& aFileName );

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

unsigned int Part1( const std::string& aFileName )
{
	const auto& distressSignals = CreateUnorderedContainerFromFile<std::list<CDistressSignal>>( aFileName );
	unsigned int result{ 0 };
	for( auto signalIt = distressSignals.cbegin(); signalIt != distressSignals.cend(); ++signalIt )
		if( ( *signalIt ).IsInOrder() )
		{
			result += static_cast< unsigned int >( std::distance( distressSignals.cbegin(), signalIt ) + 1 );
			std::cout << ( std::distance( distressSignals.cbegin(), signalIt ) + 1 ) << std::endl;
		}
	return result;
}

unsigned int Part2( const std::string& aFileName )
{
	return static_cast< unsigned int >( aFileName.size() );
}

}