#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>

#include "year.h"
#include "day.h"
#include "FileUtils.h"

#include "CInstruction.h"
#include "CCPU.h"
#include "CDisplay.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/input.txt"s;
static const std::string EXAMPLE_FILE_NAME = "../../../../"s + YEAR + "/"s + DAY + "/example.txt"s;
long Part1( const std::string& aFileName );
CDisplay Part2( const std::string& aFileName );

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

long Part1( const std::string& aFileName )
{
	const auto& instructions = CreateUnorderedContainerFromFile<std::list<CInstruction>>( aFileName );
	CCPU cpu;
	std::ranges::for_each( instructions, [ &cpu ]( const auto& aInstruction ) { cpu.PerformInstruction( aInstruction ); } );
	const std::vector<unsigned int> cycles{ 20,60,100,140,180,220 };
	return std::accumulate( cycles.cbegin(), cycles.cend(), long{ 0 }, [ &cpu ]( const long& aResult, const unsigned int& aCycle ) { return aResult + cpu.SignalStrength( aCycle ); } );
}

CDisplay Part2( const std::string& aFileName )
{
	const auto& instructions = CreateUnorderedContainerFromFile<std::list<CInstruction>>( aFileName );
	CCPU cpu;
	std::ranges::for_each( instructions, [ &cpu ]( const auto& aInstruction ) { cpu.PerformInstruction( aInstruction ); } );
	return CDisplay{ cpu, 40 };
}

}