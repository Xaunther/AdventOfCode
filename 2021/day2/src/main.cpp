#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

#include "CSubmarinePosition.h"
#include "CMovement.h"

#include "FileUtils.h"

namespace
{

static const std::string INPUT_FILE_NAME = "../../../../2021/day2/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../2021/day2/example.txt";

int Part1( const std::string& aFileName );
int Part2( const std::string& aFileName );
int main();

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

int Part1( const std::string& aFileName )
{
	const auto& movements = CreateVectorFromFile<CMovement>( aFileName );
	CSubmarinePosition submarinePosition;
	for( const auto& movement : movements )
		submarinePosition.Move( movement );
	return submarinePosition.GetPosition().first * submarinePosition.GetPosition().second;
}

int Part2( const std::string& aFileName )
{
	const auto& movements = CreateVectorFromFile<CMovement>( aFileName );
	CSubmarinePosition submarinePosition;
	for( const auto& movement : movements )
		submarinePosition.MoveWithAim( movement );
	return submarinePosition.GetPosition().first * submarinePosition.GetPosition().second;
}

}