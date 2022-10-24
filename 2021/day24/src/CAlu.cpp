#include "CAlu.h"

CAlu::CAlu():
	mNumbers( { 0, 0, 0, 0 } )
{
}

bool operator<( const CAlu& aLHS, const CAlu& aRHS )
{
	return aLHS.mNumbers < aRHS.mNumbers;
}

const int& CAlu::GetNumber( const CAlu::NUMBER& aNUMBER ) const
{
	return mNumbers[ static_cast< int >( aNUMBER ) ];
}

int& CAlu::operator[]( const CAlu::NUMBER& aNUMBER )
{
	return mNumbers[ static_cast< int >( aNUMBER ) ];
}
