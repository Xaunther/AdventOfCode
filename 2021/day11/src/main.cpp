#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "FileUtils.h"
#include "CCavern.h"

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
	auto cavern = CreateFromFile<CCavern>( aFileName );
	cavern.PerformSteps( 100 );
	return cavern.GetFlashes();
}

size_t Part2( const std::string& aFileName )
{
	auto cavern = CreateFromFile<CCavern>( aFileName );
	cavern.PerformStepsUntilSync();
	return cavern.GetTotalSteps();
}

}