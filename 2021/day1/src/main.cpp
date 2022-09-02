#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
std::vector<int> IncreaseVector( const std::vector<int>& aVector );
std::vector<int> ThreeSumVector( const std::vector<int>& aVector );
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

std::vector<int> IncreaseVector( const std::vector<int>& aVector )
{
	std::vector<int> result;
	result.reserve( aVector.size() );

	std::adjacent_difference( aVector.cbegin(), aVector.cend(), std::back_inserter( result ) );

	return result;
}

std::vector<int> ThreeSumVector( const std::vector<int>& aVector )
{
	std::vector<int> result;
	result.reserve( aVector.size() - 2 );

	for( auto vectorIt = aVector.cbegin() + 2; vectorIt != aVector.cend(); ++vectorIt )
		result.push_back( *( vectorIt - 2 ) + *( vectorIt - 1 ) + *( vectorIt ) );

	return result;
}

unsigned int Part1( const std::string& aFileName )
{
	const auto& depthMeasurements = CreateVectorFromFile<int>( aFileName );
	const auto& changeMeasurements = IncreaseVector( depthMeasurements );
	return static_cast< unsigned int >( std::count_if( changeMeasurements.cbegin() + 1, changeMeasurements.cend(),
		[]( const int aMeasurement ) { return aMeasurement > 0; } ) );
}

unsigned int Part2( const std::string& aFileName )
{
	const auto& depthMeasurements = CreateVectorFromFile<int>( aFileName );
	const auto& changeMeasurements = IncreaseVector( ThreeSumVector( depthMeasurements ) );
	return static_cast< unsigned int >( std::count_if( changeMeasurements.cbegin() + 1, changeMeasurements.cend(),
		[]( const int aMeasurement ) { return aMeasurement > 0; } ) );
}

}