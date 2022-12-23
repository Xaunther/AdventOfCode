#include "CElfFlock.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <ranges>

namespace
{

using target_positions = std::array<CElfFlock::coordinates, 3>;
using cardinal_checks = std::array<target_positions, 4>;
using nearby_checks = std::array<CElfFlock::coordinates, 8>;
using elf_moves = std::array<CElfFlock::coordinates, 4>;
static const cardinal_checks& CreateCardinalChecks();
static const nearby_checks& CreateNearbyChecks();
static const elf_moves& CreateElfMoves();
inline CElfFlock::coordinates operator+( const CElfFlock::coordinates& aLHS, const CElfFlock::coordinates& aRHS );

}

std::istream& operator>>( std::istream& aInput, CElfFlock& aElfFlock )
{
	aElfFlock = CElfFlock{};
	std::size_t i = 0;
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		for( std::size_t j = 0; j < line.size(); ++j )
			if( line[ j ] == '#' )
				aElfFlock.mElvesPositions.emplace( static_cast< CElfFlock::position >( i ), static_cast< CElfFlock::position >( j ) );
		++i;
	}

	return aInput;
}

const CElfFlock::coordinates_set& CElfFlock::GetElvesPositions() const
{
	return mElvesPositions;
}

unsigned int CElfFlock::Disperse( const std::optional<unsigned int>& aRounds )
{
	const auto& cardinalChecks = CreateCardinalChecks();
	const auto& nearbyChecks = CreateNearbyChecks();
	const auto& elfMoves = CreateElfMoves();
	std::map<CElfFlock::coordinates, std::list<CElfFlock::coordinates>> elfMovements;
	std::size_t turn = 0;
	do
	{
		elfMovements.clear();
		CElfFlock::coordinates_set newElfPositions;
		// For each elf, think next move
		for( const auto& elfPosition : mElvesPositions )
		{
			// If alone, stay still
			if( std::ranges::none_of( nearbyChecks, [ &elfPosition, this ]( auto&& aNearbyCheck )
				{ return mElvesPositions.contains( elfPosition + aNearbyCheck ); } ) )
				newElfPositions.emplace_hint( newElfPositions.end(), elfPosition );
			else
			{
				//Look for clear path and add to list of movements
				std::size_t cardinalOffset = 0;
				for( ; cardinalOffset < cardinalChecks.size() && std::ranges::any_of( cardinalChecks[ ( turn + cardinalOffset ) % cardinalChecks.size() ], [ &elfPosition, this ]( auto&& aCardinalCheck )
					{ return mElvesPositions.contains( elfPosition + aCardinalCheck ); } );++cardinalOffset );
				if( cardinalOffset == cardinalChecks.size() )//Stay still
					newElfPositions.emplace_hint( newElfPositions.end(), elfPosition );
				else
					elfMovements[ elfPosition + elfMoves[ ( turn + cardinalOffset ) % elfMoves.size() ] ].push_back( elfPosition );
			}
		}
		// Run over moving elves and roll back if there are clashes
		for( const auto& elfMovement : elfMovements )
		{
			if( elfMovement.second.size() == 1 )
				newElfPositions.insert( elfMovement.first );
			else
				for( const auto& oldPosition : elfMovement.second )
					newElfPositions.insert( oldPosition );
		}
		mElvesPositions = std::move( newElfPositions );
		++turn;
	} while( ( !aRounds || turn < *aRounds ) && !elfMovements.empty() );

	return static_cast< unsigned int >( turn );
}

std::size_t CElfFlock::RectangleSize() const
{
	auto xMin = ( *mElvesPositions.cbegin() ).first;
	auto xMax = ( *mElvesPositions.crbegin() ).first + 1;
	position yMin = 0, yMax = 0;
	for( const auto& elfPosition : mElvesPositions )
	{
		yMin = std::min( yMin, elfPosition.second );
		yMax = std::max( yMax, elfPosition.second + 1 );
	}
	return static_cast< std::size_t >( yMax - yMin ) * static_cast< std::size_t >( xMax - xMin );
}

namespace
{

static const cardinal_checks& CreateCardinalChecks()
{
	static cardinal_checks result;
	//NORTH
	result[ 0 ][ 0 ] = { -1,-1 };
	result[ 0 ][ 1 ] = { -1,0 };
	result[ 0 ][ 2 ] = { -1,1 };

	//SOUTH
	result[ 1 ][ 0 ] = { 1,-1 };
	result[ 1 ][ 1 ] = { 1,0 };
	result[ 1 ][ 2 ] = { 1,1 };

	//WEST
	result[ 2 ][ 0 ] = { -1,-1 };
	result[ 2 ][ 1 ] = { 0,-1 };
	result[ 2 ][ 2 ] = { 1,-1 };

	//EAST
	result[ 3 ][ 0 ] = { -1,1 };
	result[ 3 ][ 1 ] = { 0,1 };
	result[ 3 ][ 2 ] = { 1,1 };

	return result;
}

static const nearby_checks& CreateNearbyChecks()
{
	static nearby_checks result;
	result[ 0 ] = { -1,-1 };
	result[ 1 ] = { -1,0 };
	result[ 2 ] = { -1,1 };
	result[ 3 ] = { 0,-1 };
	result[ 4 ] = { 0,1 };
	result[ 5 ] = { 1,-1 };
	result[ 6 ] = { 1,0 };
	result[ 7 ] = { 1,1 };

	return result;
}

static const elf_moves& CreateElfMoves()
{
	static elf_moves result;
	//NORTH
	result[ 0 ] = { -1,0 };

	//SOUTH
	result[ 1 ] = { 1,0 };

	//WEST
	result[ 2 ] = { 0,-1 };

	//EAST
	result[ 3 ] = { 0,1 };

	return result;
}

inline CElfFlock::coordinates operator+( const CElfFlock::coordinates& aLHS, const CElfFlock::coordinates& aRHS )
{
	return { aLHS.first + aRHS.first, aLHS.second + aRHS.second };
}

}