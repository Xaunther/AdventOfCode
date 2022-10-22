#include "CMultiGameState.h"

#include <iostream>

using CGameState = CMultiGameState::CGameState;

namespace
{

template<typename T> std::set<T> SetWithout( const std::set<T>& aSet, const T& aRemovedElement );

}

CGameState::CGameState( const CGameState::amphibod_states& aAmphibodStates ):
	mAmphibodStates( aAmphibodStates )
{
}

std::istream& operator>>( std::istream& aInput, CGameState& aGameState )
{
	for( unsigned short rowIndex = 0; rowIndex < 3;++rowIndex )
	{
		std::string rowString;
		aInput >> rowString;
		for( unsigned short colIndex = 0; colIndex < rowString.size(); ++colIndex )
		{
			switch( rowString[ colIndex ] )
			{
			case 'A':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::AMBER, CAmphibodState::position{ rowIndex,colIndex } );
				break;
			}
			case 'B':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::BRONZE, CAmphibodState::position{ rowIndex,colIndex } );
				break;
			}
			case 'C':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::COPPER, CAmphibodState::position{ rowIndex,colIndex } );
				break;
			}
			case 'D':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::DESERT, CAmphibodState::position{ rowIndex,colIndex } );
				break;
			}
			}
		}
	}


	std::string rowString;
	unsigned short rowIndex = 0;
	while( aInput >> rowString )
	{
		for( unsigned short colIndex = 0; colIndex < rowString.size(); ++colIndex )
		{
			switch( rowString[ colIndex ] )
			{
			case 'A':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::AMBER, CAmphibodState::position{ static_cast< unsigned short >( rowIndex + 3 ), static_cast< unsigned short >( colIndex + 2 ) } );
				break;
			}
			case 'B':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::BRONZE, CAmphibodState::position{ static_cast< unsigned short >( rowIndex + 3 ), static_cast< unsigned short >( colIndex + 2 ) } );
				break;
			}
			case 'C':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::COPPER, CAmphibodState::position{ static_cast< unsigned short >( rowIndex + 3 ), static_cast< unsigned short >( colIndex + 2 ) } );
				break;
			}
			case 'D':
			{
				aGameState.mAmphibodStates.emplace( CAmphibodState::TYPE::DESERT, CAmphibodState::position{ static_cast< unsigned short >( rowIndex + 3 ), static_cast< unsigned short >( colIndex + 2 ) } );
				break;
			}
			}
		}
		++rowIndex;
	}

	return aInput;
}

bool operator<( const CGameState& aLHS, const CGameState& aRHS )
{
	return aLHS.GetAmphibodStates() < aRHS.GetAmphibodStates();
}

const CGameState::amphibod_states& CGameState::GetAmphibodStates() const
{
	return mAmphibodStates;
}

bool CGameState::IsFinished( const CBurrow& aBurrow ) const
{
	for( const auto& amphibod : mAmphibodStates )
	{
		auto otherAmphibodStates = mAmphibodStates;
		otherAmphibodStates.erase( amphibod );
		if( !amphibod.IsFinished( otherAmphibodStates, aBurrow ) )
			return false;
	}
	return true;
}

CAmphibodState::energy CGameState::EnergyUsed() const
{
	CAmphibodState::energy result{ 0 };

	for( const auto& amphibod : mAmphibodStates )
		result += amphibod.GetConsumedEnergy();

	return result;
}

CGameState::game_states CGameState::Play( const CBurrow& aBurrow ) const
{
	CGameState::game_states result;

	for( const auto& amphibodState : mAmphibodStates )
	{
		const auto& baseStates = SetWithout( mAmphibodStates, amphibodState );
		for( const auto& resultAmphibodState : amphibodState.Play( aBurrow, baseStates ) )
		{
			auto resultAmphibodStates = baseStates;
			resultAmphibodStates.insert( resultAmphibodState );
			result.emplace( std::move( resultAmphibodStates ) );
		}
	}

	return result;
}

std::istream& operator>>( std::istream& aInput, CMultiGameState& aMultiGameState )
{
	CGameState gameState;
	aInput >> gameState;
	aMultiGameState.mGameStates.insert( std::move( gameState ) );
	return aInput;
}

const CMultiGameState::game_states& CMultiGameState::GetGameStates() const
{
	return mGameStates;
}

const std::optional<CMultiGameState::energy>& CMultiGameState::GetMinimumEnergy() const
{
	return mMinimumEnergy;
}

void CMultiGameState::Play( const CBurrow& aBurrow )
{
	while( !mGameStates.empty() )
	{
		game_states resultGameStates;
		for( const auto& prevGameState : mGameStates )
		{
			auto resultGameState = prevGameState.Play( aBurrow );
			resultGameStates.insert( std::make_move_iterator( resultGameState.begin() ), std::make_move_iterator( resultGameState.end() ) );
		}
		for( auto resultGameStateIt = resultGameStates.cbegin(); resultGameStateIt != resultGameStates.cend(); )
		{
			if( ( *resultGameStateIt ).IsFinished( aBurrow ) )
			{
				if( !mMinimumEnergy )
					mMinimumEnergy = ( *resultGameStateIt ).EnergyUsed();
				else
					mMinimumEnergy = std::min( *mMinimumEnergy, ( *resultGameStateIt ).EnergyUsed() );
				resultGameStateIt = resultGameStates.erase( resultGameStateIt );
			}
			else
				++resultGameStateIt;
		}
		if( mMinimumEnergy )
		{
			for( auto resultGameStateIt = resultGameStates.cbegin(); resultGameStateIt != resultGameStates.cend(); )
			{
				if( ( *resultGameStateIt ).EnergyUsed() >= *mMinimumEnergy )
					resultGameStateIt = resultGameStates.erase( resultGameStateIt );
				else
					++resultGameStateIt;
			}
		}
		mGameStates = std::move( resultGameStates );
	}
}

namespace
{

template<typename T> std::set<T> SetWithout( const std::set<T>& aSet, const T& aRemovedElement )
{
	auto result = aSet;
	result.erase( aRemovedElement );
	return result;
}

}