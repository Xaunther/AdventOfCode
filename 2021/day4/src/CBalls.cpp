#include "CBalls.h"

#include <string>
#include <algorithm>

using namespace std::string_literals;

std::istream& operator>>( std::istream& aInput, CBalls& aBalls )
{
	std::string ballsString;
	aInput >> ballsString;
	aBalls.mBalls.reserve( std::count( ballsString.cbegin(), ballsString.cend(), ',' ) + 1 );

	for( size_t endIndex = ballsString.find( "," ), startIndex = 0; startIndex != std::string::npos; endIndex = ballsString.find( ",", endIndex ) )
	{
		aBalls.mBalls.emplace_back( std::stoul( ballsString.substr( startIndex, endIndex - startIndex ) ) );
		if( endIndex != std::string::npos )
			++endIndex;
		startIndex = endIndex;
	}
	return aInput;
}

const CBalls::balls& CBalls::GetBalls() const
{
	return mBalls;
}