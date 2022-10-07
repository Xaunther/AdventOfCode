#include "CCaverns.h"

#include <iostream>

std::istream& operator>>( std::istream& aInput, CCaverns& aCaverns )
{
	while( aInput )
	{
		std::string rawString;
		aInput >> rawString;
		if( rawString.empty() )
			break;
		CCaverns::cavern leftCavern = rawString.substr( 0, rawString.find( "-" ) );
		CCaverns::cavern rightCavern = rawString.substr( rawString.find( "-" ) + 1 );
		if( leftCavern != "end" && rightCavern != "start" )
			aCaverns.mCavernMap[ leftCavern ].insert( rightCavern );
		if( rightCavern != "end" && leftCavern != "start" )
			aCaverns.mCavernMap[ rightCavern ].insert( leftCavern );
	}
	aCaverns.mCavernMap[ "end" ] = {};

	return aInput;
}

const CCaverns::cavern_map& CCaverns::GetCavernMap() const
{
	return mCavernMap;
}

