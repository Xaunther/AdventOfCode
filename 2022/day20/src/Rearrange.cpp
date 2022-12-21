#include "Rearrange.h"

#include <iostream>

namespace
{

unsigned int CalculateDestination( const int& aNumber, int aPos, const unsigned int& aSize );

}

void Rearrange( std::list<int>& aNumbers )
{
	std::list<bool> moved( aNumbers.size(), false );

	auto movedIt = moved.begin();
	for( auto numberIt = aNumbers.begin(); numberIt != aNumbers.end(); )
	{
		const auto& numberValue = *numberIt;
		const auto& nextMovedIt = std::find( std::next( movedIt ), moved.end(), false );
		const auto& nextNumberIt = std::next( numberIt, std::distance( movedIt, nextMovedIt ) );
		const auto& currentPos = static_cast< unsigned int >( std::distance( aNumbers.begin(), numberIt ) );
		const auto& destination = CalculateDestination( numberValue, currentPos,
			static_cast< unsigned int >( aNumbers.size() - 1 ) );
		const auto& destinationNumberIt = std::next( numberIt, static_cast< int >( destination ) - static_cast< int >( currentPos ) + ( destination > currentPos ? 1 : 0 ) );
		const auto& destinationMovedIt = std::next( movedIt, static_cast< int >( destination ) - static_cast< int >( currentPos ) + ( destination > currentPos ? 1 : 0 ) );

		*movedIt = true;
		if( destinationNumberIt != numberIt )
		{
			//Perform extraction
			aNumbers.splice( destinationNumberIt, aNumbers, numberIt );
			moved.splice( destinationMovedIt, moved, movedIt );
		}
		numberIt = nextNumberIt;
		movedIt = nextMovedIt;
	}
}

namespace
{

unsigned int CalculateDestination( const int& aNumber, int aPos, const unsigned int& aSize )
{
	aPos += aNumber;
	if( aPos < 0 )
		do { aPos += aSize; } while( aPos < 0 );
	else
		aPos = aPos % aSize;
	return aPos;
}

}