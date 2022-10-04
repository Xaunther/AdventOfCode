#include "CFloorProfile.h"

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <numeric>
#include <algorithm>

namespace
{

std::list<std::pair<CFloorProfile::height_map::value_type::value_type, std::pair<size_t, size_t>>> FindLowPoints( const CFloorProfile::height_map& aHeightMap );
std::vector<size_t> FindBasins( const CFloorProfile::height_map& aHeightMap );
size_t CalculateBasinSize( const CFloorProfile::height_map& aHeightMap, const size_t& aRowIndex, const size_t& aColIndex );
bool IsLowPoint( const CFloorProfile::height_map& aHeightMap, const size_t& aRowIndex, const size_t& aColIndex );

}

std::istream& operator>>( std::istream& aInput, CFloorProfile& aDisplay )
{
	while( aInput )
	{
		std::string rowString;
		aInput >> rowString;
		if( rowString.empty() )
			break;
		CFloorProfile::height_map::value_type rowInts;
		rowInts.reserve( rowString.size() );
		for( const auto& height : rowString )
			rowInts.emplace_back( static_cast< unsigned short >( height - 48 ) );
		aDisplay.mHeightMap.emplace_back( std::move( rowInts ) );
	}
	return aInput;
}

size_t CFloorProfile::CalculateRiskLevel() const
{
	size_t result = 0;

	const auto& lowPoints = FindLowPoints( mHeightMap );
	for( const auto& lowPoint : lowPoints )
		result += lowPoint.first;

	return result;
}

size_t CFloorProfile::CalculateBasinFactor() const
{
	auto basinSizes = FindBasins( mHeightMap );
	std::sort( basinSizes.begin(), basinSizes.end() );
	return std::accumulate( basinSizes.crbegin(), basinSizes.crbegin() + 3, static_cast< size_t >( 1 ), std::multiplies<size_t>() );
}

namespace
{

std::list<std::pair<CFloorProfile::height_map::value_type::value_type, std::pair<size_t, size_t>>> FindLowPoints( const CFloorProfile::height_map& aHeightMap )
{
	std::list<std::pair<CFloorProfile::height_map::value_type::value_type, std::pair<size_t, size_t>>> result;

	for( size_t rowIndex = 0; rowIndex < aHeightMap.size(); ++rowIndex )
		for( size_t colIndex = 0; colIndex < aHeightMap[ rowIndex ].size(); ++colIndex )
			if( IsLowPoint( aHeightMap, rowIndex, colIndex ) )
				result.emplace_back( aHeightMap[ rowIndex ][ colIndex ], std::make_pair( rowIndex, colIndex ) );

	return result;
}

std::vector<size_t> FindBasins( const CFloorProfile::height_map& aHeightMap )
{
	std::vector<size_t> result;

	const auto& lowPoints = FindLowPoints( aHeightMap );
	for( const auto& lowPoint : lowPoints )
		result.emplace_back( CalculateBasinSize( aHeightMap, lowPoint.second.first, lowPoint.second.second ) );
	return result;
}

size_t CalculateBasinSize( const CFloorProfile::height_map& aHeightMap, const size_t& aRowIndex, const size_t& aColIndex )
{
	std::set<std::pair<size_t, size_t>> basinPositions{ std::make_pair( aRowIndex, aColIndex ) };

	for( size_t heightTarget = aHeightMap[ aRowIndex ][ aColIndex ]; heightTarget < 9; ++heightTarget )
	{
		for( const auto& basinPosition : basinPositions )
		{
			// Check above
			if( basinPosition.first > 0 && aHeightMap[ basinPosition.first - 1 ][ basinPosition.second ] == heightTarget )
				basinPositions.emplace( basinPosition.first - 1, basinPosition.second );
			// Check below
			if( basinPosition.first < aHeightMap.size() - 1 && aHeightMap[ basinPosition.first + 1 ][ basinPosition.second ] == heightTarget )
				basinPositions.emplace( basinPosition.first + 1, basinPosition.second );
			// Check left
			if( basinPosition.second > 0 && aHeightMap[ basinPosition.first ][ basinPosition.second - 1 ] == heightTarget )
				basinPositions.emplace( basinPosition.first, basinPosition.second - 1 );
			// Check right
			if( basinPosition.second < aHeightMap[ basinPosition.first ].size() - 1 && aHeightMap[ basinPosition.first ][ basinPosition.second + 1 ] == heightTarget )
				basinPositions.emplace( basinPosition.first, basinPosition.second + 1 );
		}
	}

	return basinPositions.size();
}

bool IsLowPoint( const CFloorProfile::height_map& aHeightMap, const size_t& aRowIndex, const size_t& aColIndex )
{
	// Check above
	if( aRowIndex > 0 && aHeightMap[ aRowIndex - 1 ][ aColIndex ] <= aHeightMap[ aRowIndex ][ aColIndex ] )
		return false;
	// Check below
	if( aRowIndex < aHeightMap.size() - 1 && aHeightMap[ aRowIndex + 1 ][ aColIndex ] <= aHeightMap[ aRowIndex ][ aColIndex ] )
		return false;
	// Check left
	if( aColIndex > 0 && aHeightMap[ aRowIndex ][ aColIndex - 1 ] <= aHeightMap[ aRowIndex ][ aColIndex ] )
		return false;
	// Check right
	if( aColIndex < aHeightMap[ aRowIndex ].size() - 1 && aHeightMap[ aRowIndex ][ aColIndex + 1 ] <= aHeightMap[ aRowIndex ][ aColIndex ] )
		return false;

	return true;
}

}
