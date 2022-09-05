#include "CBingoState.h"

#include <optional>
#include "CBingo.h"

#include <iostream>
namespace
{

std::optional<size_t> FindCardIndexWithBingo( const CBingoState::cards_states& aCardStates );
std::optional<size_t> FindCardIndexWithoutBingo( const CBingoState::cards_states& aCardStates );

}

CBingoState::CBingoState( const size_t& aCardCount ) :
	mBallsState( 0 ),
	mCardsStates( aCardCount, CCardState{} )
{
}

const CBallsState& CBingoState::GetBallsState() const
{
	return mBallsState;
}
const CBingoState::cards_states& CBingoState::GetCardsStates() const
{
	return mCardsStates;
}

size_t CBingoState::PlayUntilBingo( const CBingo& aBingo )
{
	std::optional<size_t>cardIndexWithBingo;
	do
	{
		DrawNextBall( aBingo );
		cardIndexWithBingo = FindCardIndexWithBingo( mCardsStates );
	} while( !cardIndexWithBingo );

	return mCardsStates[ *cardIndexWithBingo ].Score( aBingo.GetCards()[ *cardIndexWithBingo ], aBingo.GetBalls().GetBalls()[ mBallsState - 1 ] );

}

size_t CBingoState::PlayUntilLastBingo( const CBingo& aBingo )
{
	size_t lastCardIndex;
	std::optional<size_t>cardIndexWithoutBingo;
	do
	{
		DrawNextBall( aBingo );
		cardIndexWithoutBingo = FindCardIndexWithoutBingo( mCardsStates );
		if( cardIndexWithoutBingo )
			lastCardIndex = *cardIndexWithoutBingo;
	} while( cardIndexWithoutBingo );

	return mCardsStates[ *cardIndexWithoutBingo ].Score( aBingo.GetCards()[ *cardIndexWithoutBingo ], aBingo.GetBalls().GetBalls()[ mBallsState - 1 ] );

}

const CBingoState::ball& CBingoState::DrawNextBall( const CBingo& aBingo )
{
	const auto& drawnBall = aBingo.GetBalls().GetBalls()[ mBallsState++ ];

	auto cardStateIt = mCardsStates.begin();
	auto cardIt = aBingo.GetCards().cbegin();
	for( ; cardStateIt != mCardsStates.end(); ++cardStateIt, ++cardIt )
	{
		const auto& drawnBallPosition = ( *cardIt ).FindNumber( drawnBall );
		if( drawnBallPosition )
			( *cardStateIt ).Mark( ( *drawnBallPosition ).first, ( *drawnBallPosition ).second );
	}

	return drawnBall;
}

namespace
{

std::optional<size_t> FindCardIndexWithBingo( const CBingoState::cards_states& aCardStates )
{
	for( auto cardStateIt = aCardStates.cbegin(); cardStateIt != aCardStates.cend(); ++cardStateIt )
		if( ( *cardStateIt ).HasBingo() )
			return std::distance( aCardStates.cbegin(), cardStateIt );

	return {};
}

std::optional<size_t> FindCardIndexWithoutBingo( const CBingoState::cards_states& aCardStates )
{
	for( auto cardStateIt = aCardStates.cbegin(); cardStateIt != aCardStates.cend(); ++cardStateIt )
		if( !( *cardStateIt ).HasBingo() )
			return std::distance( aCardStates.cbegin(), cardStateIt );

	return {};
}

}