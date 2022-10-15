#include "TrajectoryUtils.h"

#include "CProjectile.h"

#include <map>
#include <set>

using target_moves = std::set<unsigned int>;
using target_moves_counter = std::map<unsigned int, target_moves>;

namespace
{

target_moves_counter FindYTargetVelocitiesMap( const CTargetArea::range& aRangeY );
target_moves_counter FindXTargetVelocitiesMap( const CTargetArea::range& aRangeX, const unsigned int& aMaximumMoves );

target_moves MovesInsideYRange( const CTargetArea::range& aRangeY, const int& yVelocity );
target_moves MovesInsideXRange( const CTargetArea::range& aRangeX, const int& xVelocity, const unsigned int& aMaximumMoves );

bool IsInRange( const CTargetArea::range& aRange, const int& aValue );

}

std::size_t MaxY( const CTargetArea::range& aRangeY )
{
	return ( -aRangeY.first ) * ( -aRangeY.first - 1 ) / 2;
}

std::size_t CountPossibleTrajectories( const CTargetArea& aTargetArea )
{
	using velocities_set = std::set<CProjectile::velocity>;
	velocities_set result;

	const auto& yVelocities = FindYTargetVelocitiesMap( aTargetArea.GetRangeY() );
	const auto& xVelocities = FindXTargetVelocitiesMap( aTargetArea.GetRangeX(), ( *yVelocities.crbegin() ).first );

	for( const auto& yVelocity : yVelocities )
	{
		const auto& xFound = xVelocities.find( yVelocity.first );
		if( xFound != xVelocities.cend() )
			for( const auto& x : ( *xFound ).second )
				for( const auto& y : yVelocity.second )
					result.emplace( x, y );
	}

	return result.size();
}

namespace
{

target_moves_counter FindYTargetVelocitiesMap( const CTargetArea::range& aRangeY )
{
	target_moves_counter result;

	for( int yVelocity = aRangeY.first; yVelocity <= -aRangeY.first - 1; ++yVelocity )
		for( const auto& move : MovesInsideYRange( aRangeY, yVelocity ) )
			result[ move ].insert( yVelocity );

	return result;
}

target_moves_counter FindXTargetVelocitiesMap( const CTargetArea::range& aRangeX, const unsigned int& aMaximumMoves )
{
	target_moves_counter result;

	const auto& minXVelocity = static_cast< int >( ( -1. + std::sqrt( 1. + 8. * aRangeX.first ) ) / 2. ) + 1;
	for( int xVelocity = minXVelocity; xVelocity <= aRangeX.second; ++xVelocity )
		for( const auto& move : MovesInsideXRange( aRangeX, xVelocity, aMaximumMoves ) )
			result[ move ].insert( xVelocity );

	return result;
}

target_moves MovesInsideYRange( const CTargetArea::range& aRangeY, const int& yVelocity )
{
	target_moves result;

	CProjectile projectile{ CProjectile::velocity{ 0, yVelocity } };
	for( unsigned int moves = 0; projectile.GetPosition().second >= aRangeY.first; projectile.Move(), ++moves )
		if( IsInRange( aRangeY, projectile.GetPosition().second ) )
			result.insert( moves );

	return result;
}

target_moves MovesInsideXRange( const CTargetArea::range& aRangeX, const int& xVelocity, const unsigned int& aMaximumMoves )
{
	target_moves result;

	CProjectile projectile{ CProjectile::velocity{ xVelocity, 0 } };
	for( unsigned int moves = 0; projectile.GetPosition().first <= aRangeX.second && moves <= aMaximumMoves; projectile.Move(), ++moves )
		if( IsInRange( aRangeX, projectile.GetPosition().first ) )
			result.insert( moves );

	return result;
}

bool IsInRange( const CTargetArea::range& aRange, const int& aValue )
{
	return aValue >= aRange.first && aValue <= aRange.second;
}

}