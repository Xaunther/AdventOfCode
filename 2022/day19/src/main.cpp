#include <iostream>
#include <list>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "CBlueprint.h"
#include "MaxGeodesMined.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
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

unsigned int Part1( const std::string& aFileName )
{
	unsigned int result{ 0 };
	unsigned int index{ 1 };
	for( const auto& blueprint : CreateUnorderedContainerFromFile<std::list<CBlueprint>>( aFileName ) )
		result += ( index++ ) * MaxGeodesMined( blueprint, 24 );
	return result;
}

unsigned int Part2( const std::string& aFileName )
{
	const auto& blueprints = CreateUnorderedContainerFromFile<std::list<CBlueprint>>( aFileName );
	unsigned int result{ 1 };
	auto blueprintIt = blueprints.cbegin();
	for( int i = 0; i < 3 && blueprintIt != blueprints.cend(); ++i, ++blueprintIt )
		result *= MaxGeodesMined( *blueprintIt, 32 );
	return result;
}

}