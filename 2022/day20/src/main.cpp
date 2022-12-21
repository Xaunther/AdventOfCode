#include <iostream>
#include <numeric>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "Rearrange.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
long long Part1( const std::string& aFileName );
long long Part2( const std::string& aFileName );

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

long long Part1( const std::string& aFileName )
{
	auto numbers = CreateUnorderedContainerFromFile<std::list<long long>>( aFileName );
	Rearrange( numbers );
	long long result{ 0 };
	int pos0 = static_cast< int >( std::distance( numbers.begin(), std::ranges::find( numbers, 0 ) ) );
	for( const auto& N : { 1000,2000,3000 } )
		result += *std::next( numbers.cbegin(), CalculateDestination( N, pos0, numbers.size() ) );
	return result;
}

long long Part2( const std::string& aFileName )
{
	auto numbers = CreateUnorderedContainerFromFile<std::list<long long>>( aFileName );
	for( auto& number : numbers )
		number *= 811589153;
	Rearrange( numbers, 10 );
	long long result{ 0 };
	int pos0 = static_cast< int >( std::distance( numbers.begin(), std::ranges::find( numbers, 0 ) ) );
	for( const long long& N : { 1000,2000,3000 } )
		result += *std::next( numbers.cbegin(), CalculateDestination( N, pos0, numbers.size() ) );
	return result;
}

}