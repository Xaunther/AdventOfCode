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