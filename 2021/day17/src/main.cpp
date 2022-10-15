#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "TrajectoryUtils.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

std::size_t Part1( const std::string& aFileName );
std::size_t Part2( const std::string& aFileName );

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

std::size_t Part1( const std::string& aFileName )
{
	const auto& targetArea = CreateFromFile<CTargetArea>( aFileName );
	return MaxY( targetArea.GetRangeY() );
}

std::size_t Part2( const std::string& aFileName )
{
	const auto& targetArea = CreateFromFile<CTargetArea>( aFileName );
	return CountPossibleTrajectories( targetArea );
}

}