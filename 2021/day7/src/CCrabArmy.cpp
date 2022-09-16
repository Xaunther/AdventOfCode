#include "CCrabArmy.h"

#include <string>
#include <algorithm>
#include <numeric>

namespace
{

unsigned int CalculateMedian( CCrabArmy::crabs& aCrabs );
int CalculateSign( const CCrabArmy::crabs& aCrabs, const size_t& aCentralValue );
unsigned long CalculateFuelConsumption2( const CCrabArmy::crabs& aCrabs, const unsigned int& aCentralValue );

} // anonymous namespace

std::istream& operator>>( std::istream& aInput, CCrabArmy& aCrabArmy )
{
	std::string crabArmyString;
	aInput >> crabArmyString;
	aCrabArmy.mCrabs.reserve( std::count( crabArmyString.cbegin(), crabArmyString.cend(), ',' ) + 1 );

	for( size_t endIndex = crabArmyString.find( "," ), startIndex = 0; startIndex != std::string::npos; endIndex = crabArmyString.find( ",", endIndex ) )
	{
		aCrabArmy.mCrabs.emplace_back( std::stoul( crabArmyString.substr( startIndex, endIndex - startIndex ) ) );
		if( endIndex != std::string::npos )
			++endIndex;
		startIndex = endIndex;
	}
	return aInput;
}

const CCrabArmy::crabs& CCrabArmy::GetCrabs() const
{
	return mCrabs;
}

unsigned long CCrabArmy::LeastAlignFuel()
{
	unsigned long result = 0;

	const auto& median = CalculateMedian( mCrabs );
	for( const auto& crab : mCrabs )
	{
		if( crab > median )
			result += crab - median;
		else
			result += median - crab;
	}

	return result;
}

unsigned long CCrabArmy::LeastAlignFuel2() const
{
	auto mean = std::accumulate( mCrabs.cbegin(), mCrabs.cend(), static_cast< unsigned int >( 0 ) ) / static_cast< unsigned int >( mCrabs.size() );

	auto fuel = CalculateFuelConsumption2( mCrabs, mean );
	auto fuelPlus = CalculateFuelConsumption2( mCrabs, mean + 1 );
	auto fuelMinus = CalculateFuelConsumption2( mCrabs, mean - 1 );

	if( fuelPlus < fuel )
	{
		++mean;
		do
		{
			fuel = fuelPlus;
			fuelPlus = CalculateFuelConsumption2( mCrabs, ++mean );
		} while( fuelPlus < fuel );
	}
	else if( fuelMinus < fuel )
	{
		--mean;
		do
		{
			fuel = fuelMinus;
			fuelMinus = CalculateFuelConsumption2( mCrabs, --mean );
		} while( fuelMinus < fuel );
	}

	return fuel;
}

namespace
{

unsigned int CalculateMedian( CCrabArmy::crabs& aCrabs )
{
	auto nth = aCrabs.begin() + aCrabs.size() / 2;
	std::nth_element( aCrabs.begin(), nth, aCrabs.end() );
	return aCrabs[ aCrabs.size() / 2 ];
}

int CalculateSign( const CCrabArmy::crabs& aCrabs, const size_t& aCentralValue )
{
	int result = 0;

	for( const auto& crab : aCrabs )
		if( crab > aCentralValue )
			++result;
		else if( crab < aCentralValue )
			--result;

	result = result / static_cast< int >( aCrabs.size() );
	return result;
}

unsigned long CalculateFuelConsumption2( const CCrabArmy::crabs& aCrabs, const unsigned int& aCentralValue )
{
	unsigned long result = 0;

	for( const auto& crab : aCrabs )
	{
		if( crab > aCentralValue )
			result += ( crab - aCentralValue ) * ( crab - aCentralValue + 1 ) / 2;
		else
			result += ( aCentralValue - crab ) * ( aCentralValue - crab + 1 ) / 2;
	}

	return result;
}

} // anonymous namespace