#include "CPathFinder.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "CElevationMap.h"

namespace
{

std::vector<unsigned int> PossibleDestinations( const unsigned int& aOrigin, const CElevationMap& aMap, const CPathFinder::paths aPaths );

}

unsigned int CPathFinder::FindShortestPath( const CElevationMap& aMap )
{
	mPaths = paths( aMap.GetElevation().size(), paths::value_type{} );
	mPaths[ aMap.GetInitialPosition() ] = 0;
	mLatestPositions.insert( aMap.GetInitialPosition() );
	do
	{
		latest_positions newLatestPositions;
		for( const auto& latestPosition : mLatestPositions )
		{
			for( const auto& possibleDestination : PossibleDestinations( latestPosition, aMap, mPaths ) )
			{
				mPaths[ possibleDestination ] = *mPaths[ latestPosition ] + 1;
				newLatestPositions.insert( possibleDestination );
			}
		}
		mLatestPositions = std::move( newLatestPositions );
	} while( !mPaths[ aMap.GetEndPosition() ] );
	return *mPaths[ aMap.GetEndPosition() ];
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