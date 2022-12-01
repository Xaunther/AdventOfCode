#include "CElf.h"
#include <string>
#include <ranges>
#include <cctype>

std::istream& operator>>( std::istream& aInput, CElf& aElf )
{
	aElf.mCalories = 0;
	std::string inputLine;
	do
	{
		std::getline( aInput, inputLine );
		if( inputLine.empty() )
			break;
		aElf.mCalories += std::stoul( inputLine );
	} while( !aInput.eof() );

	return aInput;
}

const unsigned long& CElf::GetCalories() const
{
	return mCalories;
}