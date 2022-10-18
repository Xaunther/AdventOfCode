#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CFilter.h"
#include "CImage.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

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
	std::ifstream input;
	input.open( aFileName );
	const CFilter filter{ input };
	const CImage image{ input };

	return filter.ApplyFilter( filter.ApplyFilter( image ) ).GetLitPixels().size();
}

std::size_t Part2( const std::string& aFileName )
{
	std::ifstream input;
	input.open( aFileName );
	const CFilter filter{ input };
	CImage image{ input };
	for( int index = 0; index < 50;++index )
		image = filter.ApplyFilter( image );

	return image.GetLitPixels().size();
}

}