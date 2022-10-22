#include "CBurrow.h"

std::istream& operator>>( std::istream& aInput, CBurrow& aBurrow )
{
	aBurrow.reserve( 5 );
	for( auto rowIndex = 0; rowIndex < 3;++rowIndex )
	{
		CBurrow::value_type rowResult;
		std::string rowString;
		aInput >> rowString;
		for( const auto& inputChar : rowString )
			rowResult.push_back( inputChar != '#' );
		aBurrow.push_back( std::move( rowResult ) );
	}

	std::string rowString;
	unsigned short rowIndex = 0;
	while( aInput >> rowString )
	{
		CBurrow::value_type rowResult;
		rowResult.push_back( false );
		rowResult.push_back( false );
		for( const auto& inputChar : rowString )
			rowResult.push_back( inputChar != '#' );
		rowResult.push_back( false );
		rowResult.push_back( false );
		aBurrow.push_back( std::move( rowResult ) );
		++rowIndex;
	}

	return aInput;
}