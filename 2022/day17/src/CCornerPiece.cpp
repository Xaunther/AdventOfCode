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

CCornerPiece::positions CCornerPiece::CalculateInitialPosition( const unsigned int& aFloor ) const
{
	auto result = GetPositions();
	for( unsigned int i = 0; i < 3; ++i )
		result[ i ] = { i + 3, aFloor + 4 };
	result[ 3 ] = { 5, aFloor + 5 };
	result[ 4 ] = { 5, aFloor + 6 };
	return result;
}