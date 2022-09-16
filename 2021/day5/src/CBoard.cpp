#include "CBoard.h"

#include <algorithm>

#include "CLine.h"

const CBoard::board_count& CBoard::GetBoardCount() const
{
	return mBoardCount;
}

void CBoard::PinLine( const CLine& aLine, const bool aUseDiagonals )
{
	for( const auto& linePosition : aLine.CreateSegment( aUseDiagonals ) )
		++mBoardCount[ linePosition ];
}

unsigned int CBoard::CountOverlaps() const
{
	unsigned int result = 0;

	result += static_cast< unsigned int >( std::count_if( mBoardCount.cbegin(), mBoardCount.cend(), []( const auto& aCount ) { return aCount.second > 1; } ) );

	return result;
}