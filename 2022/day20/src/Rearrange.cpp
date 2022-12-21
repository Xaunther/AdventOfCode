#include "Rearrange.h"

#include <iostream>

int CalculateDestination( const long long& aNumber, const int& aInitialPos, const std::size_t& aSize )
{
	long long result{ aInitialPos };
	result += aNumber;
	if( result < 0 )
		do { result += aSize; } while( result < 0 );
	else
		result = result % aSize;
	return static_cast< int >( result );
}

void Rearrange( std::list<long long>& aNumbers )
{
	std::list<bool> moved( aNumbers.size(), false );

	auto movedIt = moved.begin();
	for( auto numberIt = aNumbers.begin(); numberIt != aNumbers.end(); )
	{
		const auto& numberValue = *numberIt;
		const auto& nextMovedIt = std::find( std::next( movedIt ), moved.end(), false );
		const auto& nextNumberIt = std::next( numberIt, std::distance( movedIt, nextMovedIt ) );
		const auto& currentPos = static_cast< int >( std::distance( aNumbers.begin(), numberIt ) );
		const auto& destination = CalculateDestination( numberValue, currentPos, aNumbers.size() - 1 );
		const auto& destinationNumberIt = std::next( numberIt, destination - currentPos + ( destination > currentPos ? 1 : 0 ) );
		const auto& destinationMovedIt = std::next( movedIt, destination - currentPos + ( destination > currentPos ? 1 : 0 ) );

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