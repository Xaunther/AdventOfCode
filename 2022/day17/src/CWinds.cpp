#include "CWinds.h"

std::istream& operator>>( std::istream& aInput, CWinds& aWinds )
{
	char inputChar;
	while( aInput >> inputChar )
	{
		if( inputChar == '<' )
			aWinds.mWinds.push_back( false );
		else
			aWinds.mWinds.push_back( true );
	}

	return aInput;
}

const CWinds::winds& CWinds::GetWinds() const
{
	return mWinds;
}