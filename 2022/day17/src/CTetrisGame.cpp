#include "CTetrisGame.h"

#include <algorithm>
#include <map>
namespace
{

bool CanMoveLeft( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks );
bool CanMoveRight( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks );
bool CanMoveDown( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks );

}

CTetrisGame::CTetrisGame( const CWinds& aWinds, const std::size_t& aNumGames ):
	mPieceSequence( { mHorizontalPiece, mTruenoPiece, mCornerPiece, mKiszanerPiece, mSquarePiece } ),
	mWinds( aWinds.GetWinds() )
{
	Play( aNumGames );
}

void CTetrisGame::Play( const std::size_t& aNumGames )
{
	std::map<std::array<std::size_t, 3>, std::pair<std::size_t, std::size_t>> rockHistory;
	auto windIt = mWinds.cbegin();
	for( std::size_t gameCount = 0; gameCount < aNumGames; ++gameCount )
	{
		// Select our piece and set its initial position
		auto& piece = mPieceSequence[ gameCount % mPieceSequence.size() ].get();
		piece.SetInitialPosition( GetHeight() );
		while( true )
		{
			// Moved by the wind
			if( !( *windIt ) ) // Left
			{
				if( CanMoveLeft( piece, mRocks ) )
					piece.MoveLeft();
			}
			else //Right
				if( CanMoveRight( piece, mRocks ) )
					piece.MoveRight();
			++windIt;
			if( windIt == mWinds.cend() )
				windIt = mWinds.cbegin();

			// Drop down
			if( CanMoveDown( piece, mRocks ) )
				piece.MoveDown();
			else
				break;
		}
		// Add rocks to floor and remove rows below a completed line
		AddPieceToRocks( piece );
		const auto anyRemoved = RemoveUnreachableLayers();
		if( anyRemoved )
		{
			const auto& inserted = rockHistory.insert( { std::array<std::size_t, 3>{ mRocks.size(), gameCount% mPieceSequence.size(), static_cast< std::size_t >( std::distance( mWinds.cbegin(), windIt ) ) }, { gameCount, GetHeight() } } );
			if( !inserted.second )
			{
				const auto& loopSize = gameCount - ( *inserted.first ).second.first;
				const auto& towerHeight = GetHeight() - ( *inserted.first ).second.second;
				const auto& N = ( aNumGames - gameCount - 1 ) / loopSize;
				for( auto& rock : mRocks )
					rock.first += N * towerHeight;
				rockHistory.clear();
				gameCount += N * loopSize;
			}
		}
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

void CTetrisGame::Reset()
{
	mRocks.clear();
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
		if( height - pos.second < mRocks.size() )
			mRocks[ height - pos.second ].second[ pos.first - 1 ] = true;
}

bool CTetrisGame::RemoveUnreachableLayers()
{
	if( mRocks.empty() )
		return false;
	auto rockRowIt = mRocks.begin();
	auto reachableInRow = ( *rockRowIt ).second;
	for( auto& rock : reachableInRow )
		rock = !rock;
	while( std::ranges::any_of( reachableInRow, []( auto&& aRock ) { return aRock; } ) )
	{
		++rockRowIt;
		if( rockRowIt == mRocks.end() )
			return false;
		const auto& currentRow = ( *rockRowIt ).second;
		for( unsigned int i = 0; i < WIDTH; ++i )
			reachableInRow[ i ] = reachableInRow[ i ] && !currentRow[ i ];
		for( unsigned int i = WIDTH - 1; i > 0; --i )
			if( !reachableInRow[ i - 1 ] && !currentRow[ i - 1 ] && reachableInRow[ i ] )
				reachableInRow[ i - 1 ] = true;
		for( unsigned int i = 1; i < WIDTH; ++i )
			if( !reachableInRow[ i ] && !currentRow[ i ] && reachableInRow[ i - 1 ] )
				reachableInRow[ i ] = true;
	}
	const bool result = rockRowIt + 1 != mRocks.end();
	mRocks.erase( rockRowIt + 1, mRocks.end() );
	return result;
}

namespace
{

bool CanMoveLeft( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks )
{
	if( aTetrisPiece.GetLeftmostPosition() == 1 )
		return false;
	if( aRocks.empty() || ( *aRocks.cbegin() ).first < aTetrisPiece.GetBottomPosition() )
		return true;
	const auto& height = ( *aRocks.cbegin() ).first;
	for( const auto& newPos : aTetrisPiece.ProjectLeftPositions() )
		if( height >= newPos.second && aRocks[ height - newPos.second ].second[ newPos.first - 1 ] )
			return false;
	return true;
}

bool CanMoveRight( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks )
{
	if( aTetrisPiece.GetRightmostPosition() == CTetrisGame::WIDTH )
		return false;
	if( aRocks.empty() || ( *aRocks.cbegin() ).first < aTetrisPiece.GetBottomPosition() )
		return true;
	const auto& height = ( *aRocks.cbegin() ).first;
	for( const auto& newPos : aTetrisPiece.ProjectRightPositions() )
		if( height >= newPos.second && aRocks[ height - newPos.second ].second[ newPos.first - 1 ] )
			return false;
	return true;
}

bool CanMoveDown( const ATetrisPiece& aTetrisPiece, const CTetrisGame::rocks& aRocks )
{
	if( aTetrisPiece.GetBottomPosition() == 1 )
		return false;
	if( aRocks.empty() || ( *aRocks.cbegin() ).first < aTetrisPiece.GetBottomPosition() - 1 )
		return true;
	const auto& height = ( *aRocks.cbegin() ).first;
	for( const auto& newPos : aTetrisPiece.ProjectDownPositions() )
		if( height >= newPos.second && aRocks[ height - newPos.second ].second[ newPos.first - 1 ] )
			return false;
	return true;
}

}