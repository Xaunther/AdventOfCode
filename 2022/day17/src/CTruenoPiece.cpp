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

CTruenoPiece::positions CTruenoPiece::ProjectLeftPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetLeftmostPosition(), GetTopPosition() );
	result.emplace_back( GetLeftmostPosition() - 1, GetBottomPosition() + 1 );
	result.emplace_back( GetLeftmostPosition(), GetBottomPosition() );
	return result;
}

CTruenoPiece::positions CTruenoPiece::ProjectRightPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetRightmostPosition(), GetTopPosition() );
	result.emplace_back( GetRightmostPosition() + 1, GetBottomPosition() + 1 );
	result.emplace_back( GetRightmostPosition(), GetBottomPosition() );
	return result;
}

CTruenoPiece::positions CTruenoPiece::ProjectDownPositions() const
{
	positions result;
	result.reserve( 3 );
	result.emplace_back( GetLeftmostPosition(), GetBottomPosition() );
	result.emplace_back( GetLeftmostPosition() + 1, GetBottomPosition() - 1 );
	result.emplace_back( GetRightmostPosition(), GetBottomPosition() );
	return result;
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