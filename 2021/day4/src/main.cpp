#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CBingo.h"
#include "CBingoState.h"

#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;

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
	const auto& bingo = CreateFromFile<CBingo>( aFileName );
	CBingoState bingoState( bingo.GetCards().size() );
	return bingoState.PlayUntilBingo( bingo );
}

size_t Part2( const std::string& aFileName )
{
	const auto& bingo = CreateFromFile<CBingo>( aFileName );
	CBingoState bingoState( bingo.GetCards().size() );
	return bingoState.PlayUntilLastBingo( bingo );
}

}