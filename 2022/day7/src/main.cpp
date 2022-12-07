#include <iostream>

#include "year.h"
#include "day.h"
#include "FileUtils.h"
#include "CDirectoryTree.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
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
	const auto& directoryTree = CreateFromFile<CDirectoryTree>( aFileName );
	std::size_t result = 0;
	directoryTree.SumDirectorySizesAboveThreshold( result, 100000 );
	return result;
}

std::size_t Part2( const std::string& aFileName )
{
	const auto& directoryTree = CreateFromFile<CDirectoryTree>( aFileName );
	std::size_t result = 0;
	directoryTree.SizeOfUpperBoundDirectory( result, 30000000 + directoryTree.SumDirectorySizesAboveThreshold( result, 0 ) - 70000000 );
	return result;
}

}