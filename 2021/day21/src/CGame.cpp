#include "CGame.h"
#include "ADie.h"

#include <optional>

namespace
{

ADie::rolls& operator+=( ADie::rolls& aLHS, const ADie::rolls& aRHS );
template<bool tFirstPlayer> CGame::state UpdateGameStates( const CGame::state& aState, const ADie::rolls& aRolls, const CGame::CPlayerState::position& aCellCount, const std::size_t& aTargetScore );
template<bool tFirstPlayer> std::size_t LowestScore( const CGame::state& aState );

}

CGame::CPlayerState::CPlayerState( const position& aInitialPosition ):
	mPosition( aInitialPosition ),
	mScore( 0 )
{
}

const CGame::CPlayerState::position& CGame::CPlayerState::GetPosition() const
{
	return mPosition;
}

const std::size_t& CGame::CPlayerState::GetScore() const
{
	return mScore;
}

void CGame::CPlayerState::AddScore( const std::size_t& aScore )
{
	mScore += aScore;
}

void CGame::CPlayerState::Move( const position& aCells, const position& aCellCount )
{
	mPosition += aCells;
	mPosition = mPosition % aCellCount;
	if( mPosition == 0 )
		mPosition = aCellCount;
}

bool operator<( const CGame::CPlayerState& aLHS, const CGame::CPlayerState& aRHS )
{
	if( aLHS.GetScore() < aRHS.GetScore() )
		return true;
	else if( aLHS.GetScore() > aRHS.GetScore() )
		return false;
	if( aLHS.GetPosition() < aRHS.GetPosition() )
		return true;
	//if( mPosition > aRHS.GetPosition() )
	//	return true;
	return false;
}

CGame::CGame( const cell_count& aCellCount, const std::size_t& aTargetScore, const state& aGameState ):
	mCellCount( aCellCount ),
	mGameState( aGameState ),
	mTargetScore( aTargetScore )
{
}

const CGame::state& CGame::GetState() const
{
	return mGameState;
}

const CGame::cell_count& CGame::GetCellCount() const
{
	return mCellCount;
}

std::size_t CGame::GetLowestScore() const
{
	return std::min( LowestScore<true>( mGameState ), LowestScore<false>( mGameState ) );
}

std::size_t CGame::GetMostWins() const
{
	std::pair<std::size_t, std::size_t> result{ 0, 0 };

	for( const auto& state : mGameState )
	{
		if( state.first.first.GetScore() > state.first.second.GetScore() )
			result.first += state.second;
		else
			result.second += state.second;
	}

	return std::max( result.first, result.second );
}

std::size_t CGame::CountUnfinished() const
{
	std::size_t result{ 0 };

	for( const auto& state : mGameState )
		if( state.first.first.GetScore() < mTargetScore && state.first.second.GetScore() < mTargetScore )
			result += state.second;

	return result;
}

void CGame::Play( ADie& aDie ) const
{
	while( true )
	{
		{
			ADie::rolls p1Rolls{ { unsigned short{ 0 }, 1 } };
			for( int i = 0; i < 3; ++i )
				p1Rolls += aDie.Roll();
			mGameState = UpdateGameStates<true>( mGameState, p1Rolls, mCellCount, mTargetScore );
		}
		if( CountUnfinished() == 0 )
			break;
		{
			ADie::rolls p2Rolls{ { unsigned short{ 0 }, 1 } };
			for( int i = 0; i < 3; ++i )
				p2Rolls += aDie.Roll();
			mGameState = UpdateGameStates<false>( mGameState, p2Rolls, mCellCount, mTargetScore );
		}
		if( CountUnfinished() == 0 )
			break;
	}
}

namespace
{

ADie::rolls& operator+=( ADie::rolls& aLHS, const ADie::rolls& aRHS )
{
	ADie::rolls result;

	for( const auto& lhs : aLHS )
		for( const auto& rhs : aRHS )
			result[ lhs.first + rhs.first ] += lhs.second * rhs.second;

	std::swap( aLHS, result );
	return aLHS;
}

template<bool tFirstPlayer> CGame::state UpdateGameStates( const CGame::state& aState, const ADie::rolls& aRolls, const CGame::CPlayerState::position& aCellCount, const std::size_t& aTargetScore )
{
	CGame::state result;

	for( const auto& state : aState )
	{
		if( state.first.first.GetScore() >= aTargetScore || state.first.second.GetScore() >= aTargetScore )
		{
			result[ state.first ] += state.second;
			continue;
		}
		for( const auto& roll : aRolls )
		{
			auto firstPlayerState = state.first.first;
			auto secondPlayerState = state.first.second;
			if( tFirstPlayer )
			{
				firstPlayerState.Move( roll.first, aCellCount );
				firstPlayerState.AddScore( firstPlayerState.GetPosition() );
			}
			else
			{
				secondPlayerState.Move( roll.first, aCellCount );
				secondPlayerState.AddScore( secondPlayerState.GetPosition() );
			}
			result[ std::make_pair( std::move( firstPlayerState ), std::move( secondPlayerState ) ) ] += state.second * roll.second;
		}
	}

	return result;
}

template<bool tFirstPlayer> std::size_t LowestScore( const CGame::state& aState )
{

	std::optional<std::size_t> result;

	for( const auto& state : aState )
	{
		const auto& comparedScore = tFirstPlayer ? state.first.first.GetScore() : state.first.second.GetScore();
		result = result ? std::min( *result, comparedScore ) : comparedScore;
	}

	return *result;
}

}