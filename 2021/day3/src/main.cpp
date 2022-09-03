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
template<typename T> std::vector<unsigned int> CreateSumVector( const T& aBinaries );
unsigned int CalculateOxygenRating( const std::list<CBinary>& aBinaries );
unsigned int CalculateCO2Rating( const std::list<CBinary>& aBinaries );
unsigned int CalculateRating( std::list<CBinary> aBinaries, const CBinary::E_RATE& aRate );

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
	const auto& sumVector = CreateSumVector( binaries );
	return CBinary{ sumVector, binaries.size(), CBinary::E_RATE::GAMMA }.CalculateDecimalNumber() * CBinary { sumVector, binaries.size(), CBinary::E_RATE::EPSILON }.CalculateDecimalNumber();
}

unsigned long Part2( const std::string& aFileName )
{
	auto binaries = CreateListFromFile<CBinary>( aFileName );
	return CalculateOxygenRating( binaries ) * CalculateCO2Rating( binaries );
}

template<typename T> std::vector<unsigned int> CreateSumVector( const T& aBinaries )
{
	std::vector<unsigned int> result( aBinaries.front().GetBinaryNumber().size() );
	for( const auto& binary : aBinaries )
		for( size_t index = 0;index < binary.GetBinaryNumber().size(); ++index )
			result[ index ] += static_cast< unsigned int >( binary.GetBinaryNumber()[ index ] );

	return result;
}

unsigned int CalculateOxygenRating( const std::list<CBinary>& aBinaries )
{
	return CalculateRating( aBinaries, CBinary::E_RATE::GAMMA );
}

unsigned int CalculateCO2Rating( const std::list<CBinary>& aBinaries )
{
	return CalculateRating( aBinaries, CBinary::E_RATE::EPSILON );
}

unsigned int CalculateRating( std::list<CBinary> aBinaries, const CBinary::E_RATE& aRate )
{
	size_t searchIndex = 0;
	while( aBinaries.size() > 1 )
	{
		const auto& sumVector = CreateSumVector( aBinaries );
		const auto& keptDigit = CBinary( sumVector, aBinaries.size(), aRate ).GetBinaryNumber()[ searchIndex ];
		aBinaries.remove_if( [&keptDigit, &searchIndex]( const CBinary& aBinary ) { return aBinary.GetBinaryNumber()[ searchIndex ] != keptDigit; } );
		++searchIndex;
	}
	return aBinaries.front().CalculateDecimalNumber();
}


}