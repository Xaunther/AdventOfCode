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

const std::size_t& CTruenoPiece::GetTopPosition() const
{
	return GetPositions().front().second;
}

const std::size_t& CTruenoPiece::GetBottomPosition() const
{
	return GetPositions().back().second;
}

CTruenoPiece::positions CTruenoPiece::CalculateInitialPosition( const std::size_t& aFloor ) const
{
	auto result = GetPositions();
	result.front() = { 4, aFloor + 6 };
	for( unsigned int i = 0; i < 3; ++i )
		result[ i + 1 ] = { i + 3, aFloor + 5 };
	result.back() = { 4, aFloor + 4 };
	return result;
}