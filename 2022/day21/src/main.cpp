#include <iostream>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "MonkeyUtils.h"

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
	auto monkeys = CreateUnorderedContainerFromFile<std::list<CMonkey>>( aFileName );
	return CalculateMonkeyNumber( monkeys, "root" );
}

long long Part2( const std::string& aFileName )
{
	auto monkeys = CreateUnorderedContainerFromFile<std::list<CMonkey>>( aFileName );
	return CalculateHumanNumber( monkeys, "root", "humn" );
}

}