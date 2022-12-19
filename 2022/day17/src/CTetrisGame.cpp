#include "CTetrisGame.h"

CTetrisGame::CTetrisGame( const CWinds& aWinds, const std::size_t& aNumGames ):
	mPieceSequence( { mHorizontalPiece, mTruenoPiece, mCornerPiece, mKiszanerPiece, mSquarePiece } ),
	mWinds( aWinds.GetWinds() )
{
	Play( aNumGames );
}

void CTetrisGame::Play( const std::size_t& aNumGames )
{

}

const CWinds::winds& CTetrisGame::GetWinds() const
{
	return mWinds;
}

std::size_t CTetrisGame::GetHeight() const
{
	return mRocks.empty() ? 0 : ( *mRocks.begin() ).first;
}