#include "CCornerPiece.h"

CCornerPiece::CCornerPiece():
	ATetrisPiece( positions( 5, { 0,0 } ) )
{
}

const std::size_t& CCornerPiece::GetLeftmostPosition() const
{
	return GetPositions().front().first;
}

const std::size_t& CCornerPiece::GetRightmostPosition() const
{
	return GetPositions().back().first;
}

const std::size_t& CCornerPiece::GetTopPosition() const
{
	return GetPositions().back().second;
}

const std::size_t& CCornerPiece::GetBottomPosition() const
{
	return GetPositions().front().second;
}

CCornerPiece::positions CCornerPiece::ProjectLeftPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetLeftmostPosition() - 1, GetBottomPosition() );
	result.emplace_back( GetRightmostPosition() - 1, GetBottomPosition() + 1 );
	result.emplace_back( GetRightmostPosition() - 1, GetTopPosition() );
	return result;
}

CCornerPiece::positions CCornerPiece::ProjectRightPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetRightmostPosition() + 1, GetBottomPosition() );
	result.emplace_back( GetRightmostPosition() + 1, GetBottomPosition() + 1 );
	result.emplace_back( GetRightmostPosition() + 1, GetTopPosition() );
	return result;
}

CCornerPiece::positions CCornerPiece::ProjectDownPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetLeftmostPosition(), GetBottomPosition() - 1 );
	result.emplace_back( GetLeftmostPosition() + 1, GetBottomPosition() - 1 );
	result.emplace_back( GetRightmostPosition(), GetBottomPosition() - 1 );
	return result;
}

CCornerPiece::positions CCornerPiece::CalculateInitialPosition( const std::size_t& aFloor ) const
{
	auto result = GetPositions();
	for( unsigned int i = 0; i < 3; ++i )
		result[ i ] = { i + 3, aFloor + 4 };
	result[ 3 ] = { 5, aFloor + 5 };
	result[ 4 ] = { 5, aFloor + 6 };
	return result;
}