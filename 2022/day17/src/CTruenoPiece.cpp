#include "CTruenoPiece.h"

CTruenoPiece::CTruenoPiece():
	ATetrisPiece( positions( 5, { 0,0 } ) )
{
}

const std::size_t& CTruenoPiece::GetLeftmostPosition() const
{
	return GetPositions()[ 1 ].first;
}

const std::size_t& CTruenoPiece::GetRightmostPosition() const
{
	return GetPositions()[ 3 ].first;
}

CTruenoPiece::positions CTruenoPiece::CalculateInitialPosition( const unsigned int& aFloor ) const
{
	auto result = GetPositions();
	result.front() = { 4, aFloor + 6 };
	for( unsigned int i = 0; i < 3; ++i )
		result[ i + 1 ] = { i + 3, aFloor + 5 };
	result.back() = { 4, aFloor + 4 };
	return result;
}