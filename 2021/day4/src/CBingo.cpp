#include "CBingo.h"

std::istream& operator>>( std::istream& aInput, CBingo& aBingo )
{
	aInput >> aBingo.mBalls;
	CCard card;
	while( aInput >> card )
		aBingo.mCards.emplace_back( std::move( card ) );
	return aInput;
}

const CBalls& CBingo::GetBalls() const
{
	return mBalls;
}

const CBingo::cards& CBingo::GetCards() const
{
	return mCards;
}