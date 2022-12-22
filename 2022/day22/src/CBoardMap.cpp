#include "CBoardMap.h"

#include <iostream>
#include <string>

namespace
{

CBoardMap::row CreateRow( std::string_view aLine );
std::istream& operator>>( std::istream& aInput, CBoardMap::instructions& aInstructions );

struct CPlayerState
{
	explicit CPlayerState( const CBoardMap::board_map& aBoardMap );

	void ExecuteInstruction( const CBoardMap::board_map& aBoardMap, const CBoardMap::instruction& aInstruction );

private:
	CBoardMap::position NextRow( const CBoardMap::board_map& aBoardMap ) const;
	CBoardMap::position PrevRow( const CBoardMap::board_map& aBoardMap ) const;

public:
	CBoardMap::position mRowPosition;
	CBoardMap::position mColPosition;
	CBoardMap::EDirection mDirection;
};

}

std::istream& operator>>( std::istream& aInput, CBoardMap& aBoardMap )
{
	aBoardMap = CBoardMap{};
	std::string lineInput;
	std::getline( aInput, lineInput );
	do
	{
		aBoardMap.mBoardMap.push_back( CreateRow( lineInput ) );
		lineInput.clear();
		std::getline( aInput, lineInput );
	} while( lineInput != "" );

	return aInput >> aBoardMap.mInstructions;
}

const CBoardMap::board_map& CBoardMap::GetBoardMap() const
{
	return mBoardMap;
}

const CBoardMap::instructions& CBoardMap::GetInstructions() const
{
	return mInstructions;
}

std::size_t CBoardMap::FinalPassword() const
{
	CPlayerState playerState{ GetBoardMap() };

	for( const auto& inst : mInstructions )
		playerState.ExecuteInstruction( GetBoardMap(), inst );

	return 1000 * static_cast< std::size_t >( playerState.mRowPosition + 1 )
		+ 4 * static_cast< std::size_t >( playerState.mColPosition + 1 )
		+ static_cast< std::size_t >( playerState.mDirection );
}

namespace
{

CBoardMap::row CreateRow( std::string_view aLine )
{
	CBoardMap::row result;

	CBoardMap::position col = 0;
	for( ; aLine[ col ] == ' '; ++col );
	result.first.first = col;
	result.second.reserve( aLine.size() - col );
	for( ; col < aLine.size(); ++col )
		result.second.push_back( aLine[ col ] == '#' );
	result.first.second = col;

	return result;
}

std::istream& operator>>( std::istream& aInput, CBoardMap::instructions& aInstructions )
{
	CBoardMap::position length;
	char dir;
	while( aInput >> length >> dir )
		aInstructions.emplace_back( length, dir == 'L' ? CBoardMap::EDirection::LEFT : CBoardMap::EDirection::RIGHT );

	aInstructions.emplace_back( length, CBoardMap::EDirection::DOWN );
	return aInput;
}

CPlayerState::CPlayerState( const CBoardMap::board_map& aBoardMap ):
	mRowPosition( 0 ),
	mColPosition( aBoardMap.front().first.first ),
	mDirection( CBoardMap::EDirection::RIGHT )
{
}

void CPlayerState::ExecuteInstruction( const CBoardMap::board_map& aBoardMap, const CBoardMap::instruction& aInstruction )
{
	//Movement phase
	switch( mDirection )
	{
	case CBoardMap::EDirection::RIGHT:
	{
		for( CBoardMap::position moveCount = 0; moveCount < aInstruction.first; ++moveCount )
		{
			CBoardMap::position nextCol = ( mColPosition < aBoardMap[ mRowPosition ].first.second - 1 ) ? ( mColPosition + 1 ) : aBoardMap[ mRowPosition ].first.first;
			if( aBoardMap[ mRowPosition ].second[ nextCol - aBoardMap[ mRowPosition ].first.first ] )
				break;
			mColPosition = nextCol;
		}
		break;
	}
	case CBoardMap::EDirection::DOWN:
	{
		for( CBoardMap::position moveCount = 0; moveCount < aInstruction.first; ++moveCount )
		{
			const auto nextRow = NextRow( aBoardMap );
			if( aBoardMap[ nextRow ].second[ mColPosition - aBoardMap[ nextRow ].first.first ] )
				break;
			mRowPosition = nextRow;
		}
		break;
	}
	case CBoardMap::EDirection::LEFT:
	{
		for( CBoardMap::position moveCount = 0; moveCount < aInstruction.first; ++moveCount )
		{
			CBoardMap::position prevCol = mColPosition > aBoardMap[ mRowPosition ].first.first ? ( mColPosition - 1 ) : ( aBoardMap[ mRowPosition ].first.second - 1 );
			if( aBoardMap[ mRowPosition ].second[ prevCol - aBoardMap[ mRowPosition ].first.first ] )
				break;
			mColPosition = prevCol;
		}
		break;
	}
	case CBoardMap::EDirection::UP:
	{
		for( CBoardMap::position moveCount = 0; moveCount < aInstruction.first; ++moveCount )
		{
			const auto prevRow = PrevRow( aBoardMap );
			if( aBoardMap[ prevRow ].second[ mColPosition - aBoardMap[ prevRow ].first.first ] )
				break;
			mRowPosition = prevRow;
		}
		break;
	}
	}

	//Rotation phase
	switch( aInstruction.second )
	{
	case CBoardMap::EDirection::LEFT:
	{
		mDirection = static_cast< CBoardMap::EDirection >( ( static_cast< int >( mDirection ) + 3 ) % 4 );
		break;
	}
	case CBoardMap::EDirection::RIGHT:
	{
		mDirection = static_cast< CBoardMap::EDirection >( ( static_cast< int >( mDirection ) + 1 ) % 4 );
		break;
	}
	default: break;
	}
}

CBoardMap::position CPlayerState::NextRow( const CBoardMap::board_map& aBoardMap ) const
{
	CBoardMap::position result = mRowPosition + 1;
	for( ; aBoardMap[ result % aBoardMap.size() ].first.first > mColPosition || aBoardMap[ result % aBoardMap.size() ].first.second <= mColPosition; ++result );
	return result % aBoardMap.size();
}

CBoardMap::position CPlayerState::PrevRow( const CBoardMap::board_map& aBoardMap ) const
{
	CBoardMap::position result = static_cast< CBoardMap::position >( mRowPosition + aBoardMap.size() - 1 );
	for( ; aBoardMap[ result % aBoardMap.size() ].first.first > mColPosition || aBoardMap[ result % aBoardMap.size() ].first.second <= mColPosition; --result );
	return result % aBoardMap.size();
}

}