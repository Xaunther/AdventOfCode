#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CBinary.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;

unsigned long Part1( const std::string& aFileName );
unsigned long Part2( const std::string& aFileName );

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

unsigned long Part1( const std::string& aFileName )
{
	const auto& binaries = CreateVectorFromFile<CBinary>( aFileName );
	std::vector<unsigned int> sumVector( binaries.front().GetBinaryNumber().size() );
	for( const auto& binary : binaries )
		for( size_t index = 0;index < binary.GetBinaryNumber().size(); ++index )
			sumVector[ index ] += static_cast< unsigned int >( binary.GetBinaryNumber()[ index ] );
	return CBinary{ sumVector, binaries.size(), CBinary::E_RATE::GAMMA }.CalculateDecimalNumber() * CBinary { sumVector, binaries.size(), CBinary::E_RATE::EPSILON }.CalculateDecimalNumber();
}

unsigned long Part2( const std::string& aFileName )
{
	return 0;
}

}