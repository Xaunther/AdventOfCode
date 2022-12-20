#include "CSquarePiece.h"

CSquarePiece::CSquarePiece():
	ATetrisPiece( positions( 4, { 0,0 } ) )
{
}

const std::size_t& CSquarePiece::GetLeftmostPosition() const
{
	return GetPositions().front().first;
}

const std::size_t& CSquarePiece::GetRightmostPosition() const
{
	return GetPositions().back().first;
}

const std::size_t& CSquarePiece::GetTopPosition() const
{
	return GetPositions().back().second;
}

const std::size_t& CSquarePiece::GetBottomPosition() const
{
	return GetPositions().front().second;
}

CSquarePiece::positions CSquarePiece::ProjectLeftPositions() const
{
	positions result;
	result.reserve( 2 );
	result.emplace_back( GetLeftmostPosition() - 1, GetTopPosition() );
	result.emplace_back( GetLeftmostPosition() - 1, GetBottomPosition() );
	return result;
}

CSquarePiece::positions CSquarePiece::ProjectRightPositions() const
{
	positions result;
	result.reserve( 2 );
	result.emplace_back( GetRightmostPosition() + 1, GetTopPosition() );
	result.emplace_back( GetRightmostPosition() + 1, GetBottomPosition() );
	return result;
}

CSquarePiece::positions CSquarePiece::ProjectDownPositions() const
{
	positions result;
	result.reserve( 2 );
	result.emplace_back( GetLeftmostPosition(), GetBottomPosition() - 1 );
	result.emplace_back( GetRightmostPosition(), GetBottomPosition() - 1 );
	return result;
}

CSquarePiece::positions CSquarePiece::CalculateInitialPosition( const std::size_t& aFloor ) const
{
	auto result = GetPositions();
	for( unsigned int i = 0; i < 2; ++i )
	{
		result[ i ] = { i + 3, aFloor + 4 };
		result[ i + 2 ] = { i + 3, aFloor + 5 };
	}
	return result;
}