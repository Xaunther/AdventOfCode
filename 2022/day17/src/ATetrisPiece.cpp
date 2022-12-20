#include "ATetrisPiece.h"

ATetrisPiece::ATetrisPiece( const positions& aPositions ):
	mPositions( aPositions )
{
}


const ATetrisPiece::positions& ATetrisPiece::GetPositions() const
{
	return mPositions;
}

void ATetrisPiece::MoveLeft()
{
	for( auto& position : mPositions )
		--position.first;
}

void ATetrisPiece::MoveRight()
{
	for( auto& position : mPositions )
		++position.first;
}

void ATetrisPiece::MoveDown()
{
	for( auto& position : mPositions )
		--position.second;
}

void ATetrisPiece::MoveUp( const std::size_t& aYCount )
{
	for( auto& position : mPositions )
		position.second += aYCount;
}

ATetrisPiece::positions ATetrisPiece::ProjectLeftPositions() const
{
	positions result = mPositions;
	for( auto& position : result )
		--position.first;
	return result;
}

ATetrisPiece::positions ATetrisPiece::ProjectRightPositions()const
{
	positions result = mPositions;
	for( auto& position : result )
		++position.first;
	return result;
}

ATetrisPiece::positions ATetrisPiece::ProjectDownPositions()const
{
	positions result = mPositions;
	for( auto& position : result )
		--position.second;
	return result;
}

void ATetrisPiece::SetInitialPosition( const std::size_t& aFloor )
{
	mPositions = this->CalculateInitialPosition( aFloor );
}

