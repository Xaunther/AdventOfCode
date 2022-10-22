#include "CAmphibodState.h"

#include <vector>

namespace
{

std::size_t Distance( const CAmphibodState::position& aLHS, const CAmphibodState::position& aRHS );
std::vector<CAmphibodState::position> PossibleDestinations( const CAmphibodState& aAmphibodState, const CBurrow& aBurrow, const CAmphibodState::amphibod_states& aOtherAmphibodStates );
CAmphibodState::position::second_type RoomIndex( const CAmphibodState& aAmphibodState );
CAmphibodState::position::first_type RoomAvailable( const CAmphibodState& aAmphibodState, const CAmphibodState::amphibod_states& aOtherAmphibodStates, const CBurrow& aBurrow );
bool CanReach( const CAmphibodState::position& aTo, const CAmphibodState::position& aFrom, const CAmphibodState::amphibod_states& aOtherAmphibodStates );
bool IsOccupied( const CAmphibodState::position& aPosition, const CAmphibodState::amphibod_states& aOtherAmphibodStates );

}

CAmphibodState::CAmphibodState( const TYPE& aType, const position& aPosition ):
	mRequiredEnergy( RequiredEnergy( aType ) ),
	mPosition( aPosition )
{
}

CAmphibodState::CAmphibodState( const energy& aRequiredEnergy, const position& aPosition, const energy& aConsumedEnergy ):
	mPosition( aPosition ),
	mRequiredEnergy( aRequiredEnergy ),
	mConsumedEnergy( aConsumedEnergy )
{
}

bool operator<( const CAmphibodState& aLHS, const CAmphibodState& aRHS )
{
	if( aLHS.GetRequiredEnergy() < aRHS.GetRequiredEnergy() )
		return true;
	else if( aLHS.GetRequiredEnergy() > aRHS.GetRequiredEnergy() )
		return false;

	if( aLHS.GetConsumedEnergy() < aRHS.GetConsumedEnergy() )
		return true;
	else if( aLHS.GetConsumedEnergy() > aRHS.GetConsumedEnergy() )
		return false;

	return  aLHS.GetPosition() < aRHS.GetPosition();
}

const CAmphibodState::position& CAmphibodState::GetPosition() const
{
	return mPosition;
}

const CAmphibodState::energy& CAmphibodState::GetRequiredEnergy() const
{
	return mRequiredEnergy;
}

const CAmphibodState::energy& CAmphibodState::GetConsumedEnergy() const
{
	return mConsumedEnergy;
}

CAmphibodState::amphibod_states CAmphibodState::Play( const CBurrow& aBurrow, const amphibod_states& aOtherAmphibodStates ) const
{
	amphibod_states result;

	for( const auto& possibleDestination : PossibleDestinations( *this, aBurrow, aOtherAmphibodStates ) )
		result.emplace( mRequiredEnergy, possibleDestination, mConsumedEnergy + mRequiredEnergy * Distance( possibleDestination, mPosition ) );
	return result;
}

CAmphibodState::energy CAmphibodState::RequiredEnergy( const TYPE& aType )
{
	switch( aType )
	{
	case TYPE::AMBER: return 1;
	case TYPE::BRONZE: return 10;
	case TYPE::COPPER: return 100;
	case TYPE::DESERT: return 1000;
	default: return 0;
	}
}

bool CAmphibodState::IsFinished( const amphibod_states& aOtherAmphibodStates, const CBurrow& aBurrow ) const
{
	return( mPosition.first > 1 && mPosition.second == RoomIndex( *this ) && RoomAvailable( *this, aOtherAmphibodStates, aBurrow ) > 0 );
}

namespace
{

std::size_t Distance( const CAmphibodState::position& aLHS, const CAmphibodState::position& aRHS )
{
	if( aLHS.second == aRHS.second )
		return std::abs( aLHS.first - aRHS.first );

	std::size_t result = std::abs( static_cast< int >( aLHS.first ) - 1 );

	result += std::abs( static_cast< int >( aLHS.second ) - static_cast< int >( aRHS.second ) );
	result += std::abs( static_cast< int >( aRHS.first ) - 1 );

	return result;
}

std::vector<CAmphibodState::position> PossibleDestinations( const CAmphibodState& aAmphibodState, const CBurrow& aBurrow, const CAmphibodState::amphibod_states& aOtherAmphibodStates )
{
	std::vector<CAmphibodState::position> result;

	if( aAmphibodState.IsFinished( aOtherAmphibodStates, aBurrow ) )
		return result;

	//If they can go to their room, just go!
	{
		const auto& roomAvailable = RoomAvailable( aAmphibodState, aOtherAmphibodStates, aBurrow );
		CAmphibodState::position resultPosition{ static_cast< CAmphibodState::position::first_type >( 1 + roomAvailable ), RoomIndex( aAmphibodState ) };
		if( roomAvailable > 0 && CanReach( resultPosition, aAmphibodState.GetPosition(), aOtherAmphibodStates ) )
			result.emplace_back( std::move( resultPosition ) );
	}
	if( result.empty() && aAmphibodState.GetPosition().first > 1 ) // If cannot move into their room but are in another room
	{
		for( CAmphibodState::position::second_type colIndex = 1; colIndex < aBurrow[ 1 ].size() - 1; ++colIndex )
		{
			if( colIndex == 3 || colIndex == 5 || colIndex == 7 || colIndex == 9 )
				continue;
			CAmphibodState::position resultPosition{ CAmphibodState::position::first_type{ 1 }, colIndex };
			if( CanReach( resultPosition, aAmphibodState.GetPosition(), aOtherAmphibodStates ) )
				result.emplace_back( std::move( resultPosition ) );
		}
	}

	return result;
}

CAmphibodState::position::second_type RoomIndex( const CAmphibodState& aAmphibodState )
{
	switch( aAmphibodState.GetRequiredEnergy() )
	{
	case 1: return 3;
	case 10: return 5;
	case 100: return 7;
	case 1000: return 9;
	default: return 0;
	}
}

CAmphibodState::position::first_type RoomAvailable( const CAmphibodState& aAmphibodState, const CAmphibodState::amphibod_states& aOtherAmphibodStates, const CBurrow& aBurrow )
{
	CAmphibodState::position::first_type result = static_cast< CAmphibodState::position::first_type >( aBurrow.size() - 3 );

	const auto& roomIndex = RoomIndex( aAmphibodState );

	for( const auto& otherAmphibodState : aOtherAmphibodStates )
	{
		const auto& otherRoomIndex = RoomIndex( otherAmphibodState );
		if( roomIndex == otherAmphibodState.GetPosition().second )
		{
			if( roomIndex != otherRoomIndex )
				return 0;
			else
				--result;
		}
	}

	return result;
}

bool CanReach( const CAmphibodState::position& aTo, const CAmphibodState::position& aFrom, const CAmphibodState::amphibod_states& aOtherAmphibodStates )
{
	auto checkingPosition = aFrom;

	while( checkingPosition != aTo && !IsOccupied( checkingPosition, aOtherAmphibodStates ) )
	{
		if( checkingPosition.first > 1 && aTo.second != checkingPosition.second ) // Advance upwards to outside of room
			--checkingPosition.first;
		else if( aTo.second == checkingPosition.second ) //Go down towards end of room
			++checkingPosition.first;
		else if( checkingPosition.first == 1 && aTo.second > checkingPosition.second ) //Go right
			++checkingPosition.second;
		else if( checkingPosition.first == 1 && aTo.second < checkingPosition.second ) //Go left
			--checkingPosition.second;
	}
	return ( checkingPosition == aTo && !IsOccupied( checkingPosition, aOtherAmphibodStates ) );
}

bool IsOccupied( const CAmphibodState::position& aPosition, const CAmphibodState::amphibod_states& aOtherAmphibodStates )
{
	const auto& found = std::find_if( aOtherAmphibodStates.cbegin(), aOtherAmphibodStates.cend(),
		[ &aPosition ]( const CAmphibodState& aAmphibodState ) { return aAmphibodState.GetPosition() == aPosition; } );
	return found != aOtherAmphibodStates.cend();
}

}