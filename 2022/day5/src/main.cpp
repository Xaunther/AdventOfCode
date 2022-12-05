#include <iostream>
#include <numeric>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CCraneSetup.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
std::string Part1( const std::string& aFileName );
std::string Part2( const std::string& aFileName );

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

std::string Part1( const std::string& aFileName )
{
	auto craneSetup = CreateFromFile<CCraneSetup>( aFileName );
	craneSetup.ExecuteInstructions9000();
	return std::accumulate( craneSetup.GetStacks().cbegin(), craneSetup.GetStacks().cend(), std::string{},
		[]( const auto& aResult, const auto& aStack ) { return aResult + std::string{ aStack.back() }; } );
}

std::string Part2( const std::string& aFileName )
{
	auto craneSetup = CreateFromFile<CCraneSetup>( aFileName );
	craneSetup.ExecuteInstructions9001();
	return std::accumulate( craneSetup.GetStacks().cbegin(), craneSetup.GetStacks().cend(), std::string{},
		[]( const auto& aResult, const auto& aStack ) { return aResult + std::string{ aStack.back() }; } );
}

}