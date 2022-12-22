#include "CBoardMap.h"

#include <array>
#include <iostream>
#include <string>

namespace
{

using vector3D = std::array<int, 3>;

CBoardMap::row CreateRow( std::string_view aLine );
std::istream& operator>>( std::istream& aInput, CBoardMap::instructions& aInstructions );
CBoardMap::cube_map CreateCubeMap( const CBoardMap::board_map& aBoardMap );

vector3D Flip( const vector3D& aV );
vector3D VecProd( const vector3D& aLHS, const vector3D& aRHS );

struct CPlayerState
{
	explicit CPlayerState( const CBoardMap::board_map& aBoardMap );

	void ExecuteInstruction( const CBoardMap::board_map& aBoardMap, const CBoardMap::instruction& aInstruction );
	void ExecuteInstruction( const CBoardMap::board_map& aBoardMap, const CBoardMap::instruction& aInstruction, const CBoardMap::cube_map& aCubeMap );

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

	aBoardMap.mCubeMap = CreateCubeMap( aBoardMap.GetBoardMap() );
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

const CBoardMap::cube_map& CBoardMap::GetCubeMap() const
{
	return mCubeMap;
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

std::size_t CBoardMap::FinalPassword2() const
{
	CPlayerState playerState{ GetBoardMap() };

	for( const auto& inst : mInstructions )
		playerState.ExecuteInstruction( GetBoardMap(), inst, GetCubeMap() );

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

CBoardMap::cube_map CreateCubeMap( const CBoardMap::board_map& aBoardMap )
{
	// Calculate cube side length
	const CBoardMap::position length = static_cast< CBoardMap::position >(
		std::distance( aBoardMap.cbegin(), std::ranges::adjacent_find( aBoardMap,
			[]( auto&& aLHS, auto&& aRHS ) { return aLHS.first != aRHS.first; } ) ) ) + 1;

	// Compute the normal vector and the vector pointing "up" for each side
	std::map<CBoardMap::range, std::pair<vector3D, vector3D>> sideMap;
	vector3D s{ 0, 0, 1 };
	vector3D d{ 0, 1, 0 };
	//Insert first row
	CBoardMap::position colIndex = aBoardMap[ 0 ].first.first;
	while( colIndex < aBoardMap[ 0 ].first.second )
	{
		sideMap.emplace( std::make_pair( CBoardMap::position{ 0 }, colIndex ), std::make_pair( s, d ) );
		//Go right
		d = VecProd( d, s );
		//Prepare side to the right of this one
		vector3D tmp = d;
		d = Flip( s );
		s = tmp;
		d = Flip( VecProd( d, s ) );
		colIndex += length;
	}

	// Now the rest of the rows
	CBoardMap::position rowIndex = length;
	while( rowIndex < aBoardMap.size() )
	{
		//Find the block that touches with the previous row
		for( colIndex = aBoardMap[ rowIndex ].first.first; colIndex < aBoardMap[ rowIndex - length ].first.first; colIndex += length );
		const auto& found = ( *sideMap.find( { static_cast< CBoardMap::position >( rowIndex - length ), colIndex } ) ).second;
		s = found.first;
		d = Flip( found.second );
		CBoardMap::position touchingColIndex = colIndex;
		//Add the touching side
		{
			vector3D tmp = d;
			d = Flip( s );
			s = tmp;
		}
		d = Flip( d );
		sideMap.emplace( std::make_pair( rowIndex, colIndex ), std::make_pair( s, d ) );
		const auto dInit = d;
		const auto sInit = s;
		//Scan to the left
		d = Flip( VecProd( d, s ) );
		while( colIndex > aBoardMap[ rowIndex ].first.first )
		{
			//Prepare side to the left of this one
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			colIndex -= length;
			sideMap.emplace( std::make_pair( rowIndex, colIndex ), std::make_pair( s, VecProd( d, s ) ) );
		}
		//Scan to the right
		colIndex = touchingColIndex + length;
		d = dInit;
		s = sInit;
		d = VecProd( d, s );
		while( colIndex < aBoardMap[ rowIndex ].first.second )
		{
			//Prepare side to the right of this one
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			sideMap.emplace( std::make_pair( rowIndex, colIndex ), std::make_pair( s, Flip( VecProd( d, s ) ) ) );
			colIndex += length;
		}
		rowIndex += length;
	}

	// We have the orientation for each side, now we just scan all the edges and fill in the result map
	CBoardMap::cube_map result;
	// Top-edges
	{
		const auto& edgeDirection = CBoardMap::EDirection::UP;
		for( const auto& side : sideMap )
		{
			s = side.second.first;
			d = side.second.second;
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			if( side.first.first == 0 || !sideMap.contains( std::make_pair( static_cast< CBoardMap::position >( side.first.first - length ), side.first.second ) ) )
			{
				const auto& targetSide = *std::ranges::find_if( sideMap, [ &s ]( auto&& side ) { return side.second.first == s; } );
				const auto& targetDirection = d == targetSide.second.second ? CBoardMap::EDirection::UP :
					Flip( d ) == targetSide.second.second ? CBoardMap::EDirection::DOWN :
					VecProd( d, targetSide.second.first ) == targetSide.second.second ? CBoardMap::EDirection::LEFT :
					CBoardMap::EDirection::RIGHT;
				if( targetDirection == CBoardMap::EDirection::UP )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( side.first.first, static_cast< CBoardMap::position >( side.first.second + i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 ), static_cast< CBoardMap::position >( targetSide.first.second + i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::DOWN )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( side.first.first, static_cast< CBoardMap::position >( side.first.second + i ) ), edgeDirection ),
							std::make_pair( std::make_pair( targetSide.first.first, static_cast< CBoardMap::position >( targetSide.first.second + length - 1 - i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::LEFT )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( side.first.first, static_cast< CBoardMap::position >( side.first.second + i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 - i ), static_cast< CBoardMap::position >( targetSide.first.second + length - 1 ) ), targetDirection ) );
				else
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( side.first.first, static_cast< CBoardMap::position >( side.first.second + i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + i ), targetSide.first.second ), targetDirection ) );
			}
		}
	}
	// Right-edges
	{
		const auto& edgeDirection = CBoardMap::EDirection::RIGHT;
		for( const auto& side : sideMap )
		{
			s = side.second.first;
			d = VecProd( side.second.second, s );
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			if( !sideMap.contains( std::make_pair( static_cast< CBoardMap::position >( side.first.first ), static_cast< CBoardMap::position >( side.first.second + length ) ) ) )
			{
				const auto& targetSide = *std::ranges::find_if( sideMap, [ &s ]( auto&& side ) { return side.second.first == s; } );
				const auto& targetDirection = d == targetSide.second.second ? CBoardMap::EDirection::UP :
					Flip( d ) == targetSide.second.second ? CBoardMap::EDirection::DOWN :
					VecProd( d, targetSide.second.first ) == targetSide.second.second ? CBoardMap::EDirection::LEFT :
					CBoardMap::EDirection::RIGHT;
				if( targetDirection == CBoardMap::EDirection::UP )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + i ), static_cast< CBoardMap::position >( side.first.second + length - 1 ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 ), static_cast< CBoardMap::position >( targetSide.first.second + i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::DOWN )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + i ), static_cast< CBoardMap::position >( side.first.second + length - 1 ) ), edgeDirection ),
							std::make_pair( std::make_pair( targetSide.first.first, static_cast< CBoardMap::position >( targetSide.first.second + length - 1 - i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::LEFT )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + i ), static_cast< CBoardMap::position >( side.first.second + length - 1 ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 - i ), static_cast< CBoardMap::position >( targetSide.first.second + length - 1 ) ), targetDirection ) );
				else
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + i ), static_cast< CBoardMap::position >( side.first.second + length - 1 ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + i ), targetSide.first.second ), targetDirection ) );
			}
		}
	}
	// Left-edges
	{
		const auto& edgeDirection = CBoardMap::EDirection::LEFT;
		for( const auto& side : sideMap )
		{
			s = side.second.first;
			d = Flip( VecProd( side.second.second, s ) );
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			if( side.first.second == 0 || !sideMap.contains( std::make_pair( static_cast< CBoardMap::position >( side.first.first ), static_cast< CBoardMap::position >( side.first.second - length ) ) ) )
			{
				const auto& targetSide = *std::ranges::find_if( sideMap, [ &s ]( auto&& side ) { return side.second.first == s; } );
				const auto& targetDirection = d == targetSide.second.second ? CBoardMap::EDirection::UP :
					Flip( d ) == targetSide.second.second ? CBoardMap::EDirection::DOWN :
					VecProd( d, targetSide.second.first ) == targetSide.second.second ? CBoardMap::EDirection::LEFT :
					CBoardMap::EDirection::RIGHT;
				if( targetDirection == CBoardMap::EDirection::UP )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 - i ), static_cast< CBoardMap::position >( side.first.second ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 ), static_cast< CBoardMap::position >( targetSide.first.second + i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::DOWN )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 - i ), static_cast< CBoardMap::position >( side.first.second ) ), edgeDirection ),
							std::make_pair( std::make_pair( targetSide.first.first, static_cast< CBoardMap::position >( targetSide.first.second + length - 1 - i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::LEFT )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 - i ), static_cast< CBoardMap::position >( side.first.second ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 - i ), static_cast< CBoardMap::position >( targetSide.first.second + length - 1 ) ), targetDirection ) );
				else
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 - i ), static_cast< CBoardMap::position >( side.first.second ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + i ), targetSide.first.second ), targetDirection ) );
			}
		}
	}

	// Bottom-edges
	{
		const auto& edgeDirection = CBoardMap::EDirection::DOWN;
		for( const auto& side : sideMap )
		{
			s = side.second.first;
			d = Flip( side.second.second );
			{
				vector3D tmp = d;
				d = Flip( s );
				s = tmp;
			}
			if( !sideMap.contains( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length ), static_cast< CBoardMap::position >( side.first.second ) ) ) )
			{
				const auto& targetSide = *std::ranges::find_if( sideMap, [ &s ]( auto&& side ) { return side.second.first == s; } );
				const auto& targetDirection = d == targetSide.second.second ? CBoardMap::EDirection::UP :
					Flip( d ) == targetSide.second.second ? CBoardMap::EDirection::DOWN :
					VecProd( d, targetSide.second.first ) == targetSide.second.second ? CBoardMap::EDirection::LEFT :
					CBoardMap::EDirection::RIGHT;
				if( targetDirection == CBoardMap::EDirection::UP )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 ), static_cast< CBoardMap::position >( side.first.second + length - 1 - i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 ), static_cast< CBoardMap::position >( targetSide.first.second + i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::DOWN )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 ), static_cast< CBoardMap::position >( side.first.second + length - 1 - i ) ), edgeDirection ),
							std::make_pair( std::make_pair( targetSide.first.first, static_cast< CBoardMap::position >( targetSide.first.second + length - 1 - i ) ), targetDirection ) );
				else if( targetDirection == CBoardMap::EDirection::LEFT )
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 ), static_cast< CBoardMap::position >( side.first.second + length - 1 - i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + length - 1 - i ), static_cast< CBoardMap::position >( targetSide.first.second + length - 1 ) ), targetDirection ) );
				else
					for( CBoardMap::position i = 0; i < length; ++i )
						result.emplace( std::make_pair( std::make_pair( static_cast< CBoardMap::position >( side.first.first + length - 1 ), static_cast< CBoardMap::position >( side.first.second + length - 1 - i ) ), edgeDirection ),
							std::make_pair( std::make_pair( static_cast< CBoardMap::position >( targetSide.first.first + i ), targetSide.first.second ), targetDirection ) );
			}
		}
	}

	return result;
}

vector3D Flip( const vector3D& aV )
{
	vector3D result;
	for( vector3D::size_type i = 0; i < aV.size(); ++i )
		result[ i ] = -aV[ i ];
	return result;
}

vector3D VecProd( const vector3D& aLHS, const vector3D& aRHS )
{
	vector3D result;
	result[ 0 ] = aLHS[ 1 ] * aRHS[ 2 ] - aLHS[ 2 ] * aRHS[ 1 ];
	result[ 1 ] = -aLHS[ 0 ] * aRHS[ 2 ] + aLHS[ 2 ] * aRHS[ 0 ];
	result[ 2 ] = aLHS[ 0 ] * aRHS[ 1 ] - aLHS[ 1 ] * aRHS[ 0 ];
	return result;
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

void CPlayerState::ExecuteInstruction( const CBoardMap::board_map& aBoardMap, const CBoardMap::instruction& aInstruction, const CBoardMap::cube_map& aCubeMap )
{
	//Movement phase
	for( CBoardMap::position moveCount = 0; moveCount < aInstruction.first; ++moveCount )
	{
		const auto& linkFound = aCubeMap.find( std::make_pair( std::make_pair( mRowPosition, mColPosition ), mDirection ) );
		if( linkFound != aCubeMap.cend() )
		{
			const auto& mapRow = aBoardMap[ ( *linkFound ).second.first.first ];
			if( mapRow.second[ ( *linkFound ).second.first.second - mapRow.first.first ] )
				break;
			mRowPosition = ( *linkFound ).second.first.first;
			mColPosition = ( *linkFound ).second.first.second;
			mDirection = ( *linkFound ).second.second;
		}
		else // Not an edge
		{
			bool hitRock{ false };
			switch( mDirection )
			{
			case CBoardMap::EDirection::RIGHT:
			{
				const auto& mapRow = aBoardMap[ mRowPosition ];
				if( mapRow.second[ mColPosition + 1 - mapRow.first.first ] )
				{
					hitRock = true;
					break;
				}
				++mColPosition;
				break;
			}
			case CBoardMap::EDirection::DOWN:
			{
				const auto& mapRow = aBoardMap[ mRowPosition + 1 ];
				if( mapRow.second[ mColPosition - mapRow.first.first ] )
				{
					hitRock = true;
					break;
				}
				++mRowPosition;
				break;
			}
			case CBoardMap::EDirection::LEFT:
			{
				const auto& mapRow = aBoardMap[ mRowPosition ];
				if( mapRow.second[ mColPosition - 1 - mapRow.first.first ] )
				{
					hitRock = true;
					break;
				}
				--mColPosition;
				break;
			}
			default:
			{
				const auto& mapRow = aBoardMap[ mRowPosition - 1 ];
				if( mapRow.second[ mColPosition - mapRow.first.first ] )
				{
					hitRock = true;
					break;
				}
				--mRowPosition;
				break;
			}
			}
			if( hitRock )
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