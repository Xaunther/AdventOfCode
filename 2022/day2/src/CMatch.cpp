#include <CMatch.h>

std::istream& operator>>( std::istream& aInput, CMatch& aMatch )
{
	char charFigure;
	aInput >> charFigure;
	aMatch.mFigures.first = CMatch::CharToFigure( charFigure );
	aInput >> charFigure;
	aMatch.mFigures.second = CMatch::CharToFigure( charFigure );
	return aInput;
}

const CMatch::figures& CMatch::GetFigures() const
{
	return mFigures;
}

unsigned long CMatch::MyScore() const
{
	auto score = static_cast< unsigned long >( mFigures.second );

	if( mFigures.first == mFigures.second )
		score += 3;
	else if( ( mFigures.second == EFigure::ROCK && mFigures.first == EFigure::SCISSORS )
		|| ( mFigures.second == EFigure::PAPER && mFigures.first == EFigure::ROCK )
		|| ( mFigures.second == EFigure::SCISSORS && mFigures.first == EFigure::PAPER ) )
		score += 6;

	return score;
}

CMatch::EFigure CMatch::CharToFigure( const char& aChar )
{
	switch( aChar )
	{
	case 'A':
	case 'X':
		return EFigure::ROCK;
	case 'B':
	case 'Y':
		return EFigure::PAPER;
	case 'C':
	case 'Z':
		return EFigure::SCISSORS;
	}
	return EFigure::ROCK;
}