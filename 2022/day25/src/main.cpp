#include <iostream>
#include <list>
#include <numeric>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CSNAFU.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
std::string Part1( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

std::string Part1( const std::string& aFileName )
{
	const auto& numbers = CreateUnorderedContainerFromFile<std::list<CSNAFU>>( aFileName );
	return std::accumulate( numbers.cbegin(), numbers.cend(), CSNAFU{}, []( const CSNAFU& aResult, const CSNAFU& aNumber ) { return aResult + aNumber; } ).GetDigits();
}

unsigned int Part2( const std::string& aFileName )
{
	return static_cast< unsigned int >( aFileName.size() );
}

}