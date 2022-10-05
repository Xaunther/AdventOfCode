#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

#include "year.h"
#include "day.h"

#include "CLine.h"
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
	const auto& system = CreateListFromFile<CLine>( aFileName );
	return std::accumulate( system.cbegin(), system.cend(), static_cast< size_t >( 0 ),
		[]( const auto& aSum, const auto& aLine ) { return aSum + aLine.CalculateSyntaxErrorScore(); } );
}

size_t Part2( const std::string& aFileName )
{
	const auto& system = CreateListFromFile<CLine>( aFileName );
	std::vector<size_t> scores;
	for( const auto& line : system )
		if( line.IsIncomplete() )
			scores.emplace_back( line.CalculateCompletionScore() );
	std::nth_element( scores.begin(), scores.begin() + scores.size() / 2, scores.end() );
	return scores[ scores.size() / 2 ];
}

}