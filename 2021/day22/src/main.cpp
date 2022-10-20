#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CReactorCore.h"
#include "CRebootStep.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";
static const std::string EXAMPLE2_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example2.txt";

std::size_t Part1( const std::string& aFileName );
std::size_t Part2( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	std::cout << "Part 2 example: " << Part2( EXAMPLE2_FILE_NAME ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

std::size_t Part1( const std::string& aFileName )
{
	const auto& rebootSteps = CreateListFromFile<CRebootStep>( aFileName );
	CReactorCore reactorCore;
	CRebootStep::range rangeLimits{ static_cast< long >( -50 ),static_cast< long >( 50 ) };
	reactorCore.Initialize( rebootSteps, rangeLimits, rangeLimits, rangeLimits );
	return reactorCore.CountLitCubes();
}

std::size_t Part2( const std::string& aFileName )
{
	const auto& rebootSteps = CreateListFromFile<CRebootStep>( aFileName );
	CReactorCore reactorCore;
	CRebootStep::range rangeLimits{ std::numeric_limits<long>::min(),std::numeric_limits<long>::max() };
	reactorCore.Initialize( rebootSteps, rangeLimits, rangeLimits, rangeLimits );
	return reactorCore.CountLitCubes();
}

}