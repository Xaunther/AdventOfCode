#include "CMap.h"

#include <iostream>
#include <list>
#include <numeric>
#include <ranges>

namespace
{

std::istream& operator>>( std::istream& aInput, CMap::sensor& aSensor );
unsigned int ManhattanDistance( const CMap::sensor& aSensor );
std::list<CMap::coordinates> AddedSegments( const CMap::coordinates aNewSegments, const std::list<CMap::coordinates>& aRowSegments );

}

std::istream& operator>>( std::istream& aInput, CMap& aMap )
{
	aMap.mBeacons.clear();
	aMap.mSensors.clear();

	CMap::sensor sensor;
	std::string word;
	while( aInput >> sensor )
	{
		aMap.mSensors[ sensor.first ] = sensor.second;
		aMap.mBeacons.insert( sensor.second );
	}
	return aInput;
}

const CMap::beacons& CMap::GetBeacons() const
{
	return mBeacons;
}

const CMap::sensors& CMap::GetSensors() const
{
	return mSensors;
}

unsigned int CMap::CountForbiddenPositions( const int& aRow ) const
{
	std::list<coordinates> rowSegments;
	for( const auto& sensor : mSensors )
	{
		const unsigned int& coveredDistance = ManhattanDistance( sensor );
		if( static_cast< unsigned int >( std::abs( aRow - sensor.first.second ) ) <= coveredDistance )
		{
			const int offset = coveredDistance - std::abs( aRow - sensor.first.second );
			for( auto& addedSegments : AddedSegments( coordinates{ sensor.first.first - offset, sensor.first.first + offset }, rowSegments ) )
				rowSegments.emplace_back( std::move( addedSegments ) );
		}
	}
	unsigned int result = static_cast< unsigned int >( std::accumulate( rowSegments.cbegin(), rowSegments.cend(), int{ 0 },
		[]( const unsigned int& aResult, const coordinates& aCoordinates ) { return aResult + aCoordinates.second + 1 - aCoordinates.first; } ) );

	for( const auto& beacon : mBeacons )
	{
		if( beacon.second == aRow )
		{
			const auto found = std::ranges::find_if( rowSegments, [ &beacon ]( auto&& aSegment ) { return aSegment.first <= beacon.first && aSegment.second >= beacon.first; } );
			if( found != rowSegments.cend() )
				--result;
		}
	}
	return result;
}


namespace
{

std::istream& operator>>( std::istream& aInput, CMap::sensor& aSensor )
{
	std::string word;
	char c;
	return aInput >> word >> word >> c >> c >> aSensor.first.first >> c >> c >> c >> aSensor.first.second >> c >> word >> word >> word >> word >> c >> c >> aSensor.second.first >> c >> c >> c >> aSensor.second.second;
}

unsigned int ManhattanDistance( const CMap::sensor& aSensor )
{
	return static_cast< unsigned int >( std::abs( aSensor.first.first - aSensor.second.first ) + std::abs( aSensor.first.second - aSensor.second.second ) );
}

std::list<CMap::coordinates> AddedSegments( const CMap::coordinates aNewSegments, const std::list<CMap::coordinates>& aRowSegments )
{
	std::list<CMap::coordinates> result = { aNewSegments };

	for( const auto& rowSegment : aRowSegments )
	{
		for( auto newSegmentIt = result.begin(); newSegmentIt != result.end(); )
		{
			auto& newSegment = *newSegmentIt;
			if( newSegment.second < rowSegment.first || newSegment.first > rowSegment.second ) {}
			else if( newSegment.first < rowSegment.first && newSegment.second > rowSegment.second )
			{
				result.emplace_back( rowSegment.second + 1, newSegment.second );
				newSegment.second = rowSegment.first - 1;
			}
			else if( newSegment.first < rowSegment.first )
				newSegment.second = rowSegment.first - 1;
			else if( newSegment.second > rowSegment.second )
				newSegment.first = rowSegment.second + 1;
			else
			{
				newSegmentIt = result.erase( newSegmentIt );
				continue;
			}
			++newSegmentIt;
		}
	}

	return result;
}

}