#include "CLanternfishPopulation.h"

#include <string>
#include <numeric>

std::istream& operator>>( std::istream& aInput, CLanternfishPopulation& aLanternfishPopulation )
{
	std::string lanternfishString;
	aInput >> lanternfishString;

	for( size_t endIndex = lanternfishString.find( "," ), startIndex = 0; startIndex != std::string::npos; endIndex = lanternfishString.find( ",", endIndex ) )
	{
		++aLanternfishPopulation.mPopulation[ std::stoul( lanternfishString.substr( startIndex, endIndex - startIndex ) ) ];
		if( endIndex != std::string::npos )
			++endIndex;
		startIndex = endIndex;
	}
	return aInput;
}

const CLanternfishPopulation::population& CLanternfishPopulation::GetPopulation() const
{
	return mPopulation;
}

unsigned long long CLanternfishPopulation::CountPopulation() const
{
	return std::accumulate( mPopulation.cbegin(), mPopulation.cend(), static_cast< unsigned long long >( 0 ),
		[]( const auto& aResult, const auto& aAge ) { return aResult + aAge.second; } );
}

void CLanternfishPopulation::PassDay( const unsigned int& aDays )
{
	for( unsigned int day = 0; day < aDays; ++day )
		PassDay();
}

void CLanternfishPopulation::PassDay()
{
	unsigned long long newBorns = 0;
	for( auto& age : mPopulation )
	{
		if( age.first == 0 )
			newBorns = age.second;
		else
			mPopulation[ age.first - 1 ] = age.second;
		age.second = 0;
	}
	mPopulation[ 6 ] += newBorns;
	mPopulation[ 8 ] = newBorns;
}