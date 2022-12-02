#include "CFixedMatch.h"

std::istream& operator>>( std::istream& aInput, CFixedMatch& aFixedMatch )
{
	char charFigure;
	aInput >> charFigure;
	aFixedMatch.mFigures.first = CMatch::CharToFigure( charFigure );
	aInput >> charFigure;
	aFixedMatch.mFigures.second = CFixedMatch::CharToOutcome( charFigure );
	return aInput;
}

const CFixedMatch::figures& CFixedMatch::GetFigures() const
{
	return mFigures;
}

unsigned long CFixedMatch::MyScore() const
{
	auto score = static_cast< unsigned long >( mFigures.second );

	if( mFigures.second == EOutcome::DRAW )
		score += static_cast< unsigned long >( mFigures.first );
	else if( mFigures.second == EOutcome::WIN )
	{
		if( mFigures.first == CMatch::EFigure::ROCK )
			score += static_cast< unsigned long >( CMatch::EFigure::PAPER );
		else if( mFigures.first == CMatch::EFigure::PAPER )
			score += static_cast< unsigned long >( CMatch::EFigure::SCISSORS );
		else
			score += static_cast< unsigned long >( CMatch::EFigure::ROCK );
	}
	else
	{
		if( mFigures.first == CMatch::EFigure::ROCK )
			score += static_cast< unsigned long >( CMatch::EFigure::SCISSORS );
		else if( mFigures.first == CMatch::EFigure::PAPER )
			score += static_cast< unsigned long >( CMatch::EFigure::ROCK );
		else
			score += static_cast< unsigned long >( CMatch::EFigure::PAPER );
	}

	return score;
}

CFixedMatch::EOutcome CFixedMatch::CharToOutcome( const char& aChar )
{
	switch( aChar )
	{
	case 'X':
		return EOutcome::LOSE;
	case 'Y':
		return EOutcome::DRAW;
	case 'Z':
		return EOutcome::WIN;
	}
	return EOutcome::LOSE;
}