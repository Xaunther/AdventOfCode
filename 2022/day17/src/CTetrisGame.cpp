#include "CTetrisGame.h"

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
			// Drop down
		}
		// Add rocks to floor and remove tiles below a completed line
	}
}

const CWinds::winds& CTetrisGame::GetWinds() const
{
	return mWinds;
}

std::size_t CTetrisGame::GetHeight() const
{
	return mRocks.empty() ? 0 : ( *mRocks.begin() ).first;
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
	}
}

bool CanMoveRight( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint )
{

}

bool CanMoveDown( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks, const CTetrisGame::rocks::const_iterator& aRockHint )
{

}


}