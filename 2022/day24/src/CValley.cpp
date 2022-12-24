#include "CValley.h"

#include "CoordinateUtils.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <ranges>
#include <set>

namespace
{

static const std::map<char, CValley::coordinates>& CreateDirectionMap();
static const std::array<CValley::coordinates, 5>& PossibleMovements();
unsigned int CalculateCycleSize( const CValley::coordinates& aSize );
inline bool IsInside( const CValley::coordinates& aPosition, const CValley::coordinates& aSize );

bool IsPrime( const unsigned int& aNumber );
using factorized_number = std::map<unsigned int, unsigned int>;
factorized_number Factorize( unsigned int aNumber );
unsigned int MCM( const factorized_number& aLHS, const factorized_number& aRHS );

}

std::istream& operator>>( std::istream& aInput, CValley& aValley )
{
	std::vector<std::string> inputRows;
	for( const auto& rowInput : std::ranges::istream_view<std::string>( aInput ) )
		inputRows.push_back( rowInput );

	// Entrance
	aValley.mStartPosition = { -1, static_cast< int >( inputRows.front().find( '.' ) ) - 1 };

	// Middle
	for( int i = 1; i < inputRows.size() - 1; ++i )
		for( int j = 1; j < inputRows[ i ].size() - 1; ++j )
			if( inputRows[ i ][ j ] != '.' )
				aValley.mBlizzards.emplace_back( CValley::coordinates{ i - 1,j - 1 }, CreateDirectionMap().at( inputRows[ i ][ j ] ) );

	// Exit
	aValley.mEndPosition = { static_cast< int >( inputRows.size() - 2 ), static_cast< int >( inputRows.back().find( '.' ) ) - 1 };

	aValley.mSize.first = static_cast< int >( inputRows.size() - 2 );
	aValley.mSize.second = static_cast< int >( inputRows.front().size() - 2 );

	return aInput;
}

const CValley::blizzards& CValley::GetBlizzards() const
{
	return mBlizzards;
}

unsigned int CValley::Traverse( const bool aInReverse )
{
	std::vector<std::set<coordinates>> historicPositions( CalculateCycleSize( mSize ), std::set<coordinates>{} );
	const auto& start = aInReverse ? mEndPosition : mStartPosition;
	const auto& end = aInReverse ? mStartPosition : mEndPosition;
	std::set<coordinates> currentPositions{ start };
	historicPositions.front() = currentPositions;

	unsigned int turns = 0;
	while( true )
	{
		++turns;
		// Update blizzard positions
		for( auto& blizzard : mBlizzards )
			blizzard.Move( mSize );
		// Try moving from every current position
		std::set<coordinates> newPositions;
		for( const auto& currentPosition : currentPositions )
		{
			for( const auto& move : PossibleMovements() )
			{
				const auto& destination = currentPosition + move;
				if( ( destination == end || destination == start || IsInside( destination, mSize ) ) &&
					std::ranges::none_of( mBlizzards, [ &move, &destination ]( auto&& aBlizzard ) { return aBlizzard.GetLocation() == destination; } ) )
				{
					if( destination == end )
						return turns;
					newPositions.insert( destination );
					historicPositions[ turns % historicPositions.size() ].insert( destination );
				}
			}
		}
		currentPositions = std::move( newPositions );
	}

	return 0;
}

namespace
{

static const std::map<char, CValley::coordinates>& CreateDirectionMap()
{
	static std::map<char, CValley::coordinates> result;
	result.emplace( '<', CValley::coordinates{ 0,-1 } );
	result.emplace( '^', CValley::coordinates{ -1,0 } );
	result.emplace( '>', CValley::coordinates{ 0,1 } );
	result.emplace( 'v', CValley::coordinates{ 1,0 } );
	return result;
}

static const std::array<CValley::coordinates, 5>& PossibleMovements()
{
	static std::array<CValley::coordinates, 5> result;

	result[ 0 ] = { 0, 0 };
	result[ 1 ] = { 0, -1 };
	result[ 2 ] = { 0, 1 };
	result[ 3 ] = { -1, 0 };
	result[ 4 ] = { 1, 0 };

	return result;
}

unsigned int CalculateCycleSize( const CValley::coordinates& aSize )
{
	const auto& firstFactors = Factorize( aSize.first );
	const auto& secondFactors = Factorize( aSize.second );
	return MCM( firstFactors, secondFactors );
}

inline bool IsInside( const CValley::coordinates& aPosition, const CValley::coordinates& aSize )
{
	return !( aPosition.first < 0 || aPosition.second < 0 || aPosition.first >= aSize.first || aPosition.second >= aSize.second );
}

bool IsPrime( const unsigned int& aNumber )
{
	for( unsigned int i = 2; i <= aNumber / 2; ++i )
		if( aNumber % i == 0 )
			return false;
	return true;
}

factorized_number Factorize( unsigned int aNumber )
{
	factorized_number result;
	for( unsigned int factor = 2; factor <= aNumber; ++factor )
	{
		if( IsPrime( factor ) )
		{
			while( aNumber % factor == 0 )
			{
				++result[ factor ];
				aNumber /= factor;
			}
		}
	}
	return result;
}

unsigned int MCM( const factorized_number& aLHS, const factorized_number& aRHS )
{
	factorized_number factoredResult{ aLHS };
	for( const auto& rhs : aRHS )
	{
		auto& added = factoredResult[ rhs.first ];
		added = std::max( added, rhs.second );
	}
	unsigned int result = 1;
	for( const auto& res : factoredResult )
		for( unsigned int i = 0; i < res.second; ++i )
			result *= res.first;
	return result;
}

}