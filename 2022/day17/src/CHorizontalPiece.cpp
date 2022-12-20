#include "CHorizontalPiece.h"

CHorizontalPiece::CHorizontalPiece():
	ATetrisPiece( positions( 4, { 0,0 } ) )
{
}

const std::size_t& CHorizontalPiece::GetLeftmostPosition() const
{
	return GetPositions().front().first;
}

const std::size_t& CHorizontalPiece::GetRightmostPosition() const
{
	return GetPositions().back().first;
}

const std::size_t& CHorizontalPiece::GetTopPosition() const
{
	return GetPositions().front().second;
}

const std::size_t& CHorizontalPiece::GetBottomPosition() const
{
	return GetPositions().front().second;
}

CHorizontalPiece::positions CHorizontalPiece::CalculateInitialPosition( const std::size_t& aFloor ) const
{
	auto result = GetPositions();
	for( unsigned int i = 0; i < result.size(); ++i )
		result[ i ] = { i + 3, aFloor + 4 };
	return result;
}