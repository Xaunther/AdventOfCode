#include "CTetrisGame.h"

#include <algorithm>
#include <iostream>
namespace
{

bool CanMoveLeft( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint );
bool CanMoveRight( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint );
bool CanMoveDown( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint );

}

CTetrisGame::CTetrisGame( const CWinds& aWinds, const std::size_t& aNumGames ):
	mPieceSequence( { mHorizontalPiece, mTruenoPiece, mCornerPiece, mKiszanerPiece, mSquarePiece } ),
	mWinds( aWinds.GetWinds() )
{
	Play( aNumGames );
}

void CTetrisGame::Play( const std::size_t& aNumGames )
{
	auto windIt = mWinds.cbegin();
	for( std::size_t gameCount = 0; gameCount < aNumGames; ++gameCount )
	{
		// Select our piece and set its initial position
		auto& piece = mPieceSequence[ gameCount % mPieceSequence.size() ].get();
		piece.SetInitialPosition( GetHeight() );
		// Set rocky floor iterator to the top of the pile
		auto rockIt = mRocks.cbegin();
		while( true )
		{
			// Moved by the wind
			if( !( *windIt ) ) // Left
			{
				if( CanMoveLeft( piece, mRocks, rockIt ) )
					piece.MoveLeft();
			}
			else //Right
				if( CanMoveRight( piece, mRocks, rockIt ) )
					piece.MoveRight();
			++windIt;
			if( windIt == mWinds.cend() )
				windIt = mWinds.cbegin();

			// Drop down
			if( CanMoveDown( piece, mRocks, rockIt ) )
				piece.MoveDown();
			else
				break;

			//Move iterator to the first rock that may interact with the falling piece
			if( rockIt != mRocks.cend() && ( *rockIt ).first > piece.GetTopPosition() )
				++rockIt;
		}
		// Add rocks to floor and remove rows below a completed line
		AddPieceToRocks( piece );
	}
	/*
	std::cout << std::endl;
	for( const auto& rockRow : mRocks )
	{
		std::cout << "|";
		for( const auto& rock : rockRow.second )
			std::cout << ( rock ? '#' : '.' );
		std::cout << "|\n";
	}
	std::cout << "+-------+\n";
	*/
}

const CWinds::winds& CTetrisGame::GetWinds() const
{
	return mWinds;
}

std::size_t CTetrisGame::GetHeight() const
{
	return mRocks.empty() ? 0 : ( *mRocks.begin() ).first;
}

void CTetrisGame::AddPieceToRocks( const ATetrisPiece& aPiece )
{
	//Add new heights
	if( GetHeight() < aPiece.GetTopPosition() )
	{
		for( std::size_t height = GetHeight() + 1; height <= aPiece.GetTopPosition(); ++height )
			mRocks.emplace_front( height, rocks::value_type::second_type{} );
	}

	const auto& height = GetHeight();

	//Add piece
	for( const auto& pos : aPiece.GetPositions() )
	{
		if( height - pos.second < mRocks.size() )
		{
			auto& rockRow = mRocks[ height - pos.second ].second;
			rockRow[ pos.first - 1 ] = true;
			if( std::ranges::all_of( rockRow, []( auto&& aRock ) { return aRock; } ) )
				mRocks.erase( mRocks.begin() + height - pos.second + 1, mRocks.end() );
		}
	}
}

namespace
{

bool CanMoveLeft( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint )
{
	if( aTetrisPiece.GetLeftmostPosition() == 1 )
		return false;
	for( const auto& newPos : aTetrisPiece.ProjectLeftPositions() )
	{
		const auto& rowFound = std::find_if( aRockHint, aRocks.cend(), [ &newPos ]( auto&& aRockRow ) { return aRockRow.first == newPos.second; } );
		if( rowFound != aRocks.cend() && ( *rowFound ).second[ newPos.first - 1 ] )
			return false;
	}
	return true;
}

bool CanMoveRight( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint )
{
	if( aTetrisPiece.GetRightmostPosition() == CTetrisGame::WIDTH )
		return false;
	for( const auto& newPos : aTetrisPiece.ProjectRightPositions() )
	{
		const auto& rowFound = std::find_if( aRockHint, aRocks.cend(), [ &newPos ]( auto&& aRockRow ) { return aRockRow.first == newPos.second; } );
		if( rowFound != aRocks.cend() && ( *rowFound ).second[ newPos.first - 1 ] )
			return false;
	}
	return true;
}

bool CanMoveDown( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint )
{
	if( aTetrisPiece.GetBottomPosition() == 1 )
		return false;
	for( const auto& newPos : aTetrisPiece.ProjectDownPositions() )
	{
		const auto& rowFound = std::find_if( aRockHint, aRocks.cend(), [ &newPos ]( auto&& aRockRow ) { return aRockRow.first == newPos.second; } );
		if( rowFound != aRocks.cend() && ( *rowFound ).second[ newPos.first - 1 ] )
			return false;
	}
	return true;
}

}