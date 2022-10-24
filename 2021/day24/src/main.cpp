#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CChecker.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

CModelNumber Part1( const std::string& aFileName );
CModelNumber Part2( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

CModelNumber Part1( const std::string& aFileName )
{
	const auto& instructions = CreateListFromFile<CInstruction>( aFileName );
	CChecker checker;
	checker.Check( instructions );
	return checker.GetMaximumValidNumber();
}

CModelNumber Part2( const std::string& aFileName )
{
	const auto& instructions = CreateListFromFile<CInstruction>( aFileName );
	CChecker checker;
	checker.Check( instructions, false );
	return checker.GetMinimumValidNumber();
}

}