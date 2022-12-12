#include "CPathFinder.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "CElevationMap.h"

namespace
{

std::vector<unsigned int> PossibleDestinations( const unsigned int& aOrigin, const CElevationMap& aMap, const CPathFinder::paths aPaths );

}

unsigned int CPathFinder::FindShortestPath( const CElevationMap& aMap, const bool aAnyPath )
{
	mPaths = paths( aMap.GetElevation().size(), false );
	if( aAnyPath )
	{
		unsigned int index{ 0 };
		for( const auto& elevation : aMap.GetElevation() )
		{
			if( elevation == 'a' )
			{
				mPaths[ index ] = true;
				mLatestPositions.insert( index );
			}
			++index;
		}

	}
	else
	{
		mPaths[ aMap.GetInitialPosition() ] = true;
		mLatestPositions.insert( aMap.GetInitialPosition() );
	}

	unsigned int result{ 0 };
	do
	{
		latest_positions newLatestPositions;
		for( const auto& latestPosition : mLatestPositions )
		{
			for( const auto& possibleDestination : PossibleDestinations( latestPosition, aMap, mPaths ) )
			{
				mPaths[ possibleDestination ] = true;
				newLatestPositions.insert( possibleDestination );
			}
		}
		mLatestPositions = std::move( newLatestPositions );
		++result;
	} while( !mPaths[ aMap.GetEndPosition() ] );
	return result;
}

namespace
{

std::vector<unsigned int>PossibleDestinations( const unsigned int& aOrigin, const CElevationMap& aMap, const CPathFinder::paths aPaths )
{
	std::vector<unsigned int> result;
	result.reserve( 4 );
	//TOP
	if( aOrigin >= aMap.GetWidth() && aMap.GetElevation()[ aOrigin ] >= aMap.GetElevation()[ aOrigin - aMap.GetWidth() ] - 1 && !aPaths[ aOrigin - aMap.GetWidth() ] )
		result.push_back( aOrigin - aMap.GetWidth() );
	//BOTTOM
	if( aOrigin + aMap.GetWidth() < aMap.GetElevation().size() && aMap.GetElevation()[ aOrigin ] >= aMap.GetElevation()[ aOrigin + aMap.GetWidth() ] - 1 && !aPaths[ aOrigin + aMap.GetWidth() ] )
		result.push_back( aOrigin + aMap.GetWidth() );
	//LEFT
	if( aOrigin % aMap.GetWidth() != 0 && aMap.GetElevation()[ aOrigin ] >= aMap.GetElevation()[ aOrigin - 1 ] - 1 && !aPaths[ aOrigin - 1 ] )
		result.push_back( aOrigin - 1 );
	//RIGHT
	if( ( aOrigin + 1 ) % aMap.GetWidth() != 0 && aMap.GetElevation()[ aOrigin ] >= aMap.GetElevation()[ aOrigin + 1 ] - 1 && !aPaths[ aOrigin + 1 ] )
		result.push_back( aOrigin + 1 );

	return result;
}

}