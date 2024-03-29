#include <iostream>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "CElfFlock.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
std::size_t Part1( const std::string& aFileName );
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

std::size_t Part1( const std::string& aFileName )
{
	auto elfFlock = CreateFromFile<CElfFlock>( aFileName );
	elfFlock.Disperse( 10 );
	return ( elfFlock.RectangleSize() - elfFlock.GetElvesPositions().size() );
}

unsigned int Part2( const std::string& aFileName )
{
	return CreateFromFile<CElfFlock>( aFileName ).Disperse();
}

}