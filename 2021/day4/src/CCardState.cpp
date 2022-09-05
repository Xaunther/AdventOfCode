#include "CCardState.h"

#include "CCard.h"

CCardState::CCardState()
{
	for( auto& row : mMarks )
		for( auto& mark : row )
			mark = false;
}

const CCardState::marks& CCardState::GetMarks() const
{
	return mMarks;
}

void CCardState::Mark( const size_t aRowIndex, const size_t aColIndex )
{
	mMarks.at( aRowIndex ).at( aColIndex ) = true;
}

bool CCardState::HasBingo() const
{
	for( const auto& row : mMarks )
	{
		bool result = true;
		for( const auto& mark : row )
			result = result && mark;
		if( result )
			return true;
	}

	for( size_t colIndex = 0; colIndex < mMarks.size(); ++colIndex )
	{
		bool result = true;
		for( size_t rowIndex = 0; rowIndex < mMarks.size(); ++rowIndex )
			result = result && mMarks[ rowIndex ][ colIndex ];
		if( result )
			return true;
	}
	return false;
}

size_t CCardState::Score( const CCard& aCard, const unsigned int& aLastBall )
{
	size_t result = 0;

	for( size_t rowIndex = 0; rowIndex < mMarks.size(); ++rowIndex )
		for( size_t colIndex = 0; colIndex < mMarks.size(); ++colIndex )
			if( !mMarks[ rowIndex ][ colIndex ] )
				result += aCard.GetNumbers()[ rowIndex ][ colIndex ];

	return result * aLastBall;
}
