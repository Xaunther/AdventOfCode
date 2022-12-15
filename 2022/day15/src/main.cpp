#include <iostream>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CMap.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
unsigned int Part1( const std::string& aFileName, const int& aRow );
std::size_t Part2( const std::string& aFileName, const int& aMaxRow );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME, 10 ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME, 2000000 ) << std::endl;
	std::cout << "Part 2 example: " << Part2( EXAMPLE_FILE_NAME, 20 ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT_FILE_NAME, 4000000 ) << std::endl;
	return 0;
}

namespace
{

unsigned int Part1( const std::string& aFileName, const int& aRow )
{
	const auto& map = CreateFromFile<CMap>( aFileName );
	return map.CountForbiddenPositions( aRow );
}

std::size_t Part2( const std::string& aFileName, const int& aMaxRow )
{
	const auto& map = CreateFromFile<CMap>( aFileName );
	return map.TuningFrequency( aMaxRow );
}

}