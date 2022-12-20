#include "CKiszanerPiece.h"

CKiszanerPiece::CKiszanerPiece():
	ATetrisPiece( positions( 4, { 0,0 } ) )
{
}

const std::size_t& CKiszanerPiece::GetLeftmostPosition() const
{
	return GetPositions().front().first;
}

const std::size_t& CKiszanerPiece::GetRightmostPosition() const
{
	return GetLeftmostPosition();
}

CKiszanerPiece::positions CKiszanerPiece::CalculateInitialPosition( const std::size_t& aFloor ) const
{
	auto result = GetPositions();
	for( unsigned int i = 0; i < result.size(); ++i )
		result[ i ] = { 3, aFloor + 4 + i };
	return result;
}