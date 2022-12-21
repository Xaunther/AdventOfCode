#include "Rearrange.h"

#include <iostream>
#include <numeric>

int CalculateDestination( const long long& aNumber, const int& aInitialPos, const std::size_t& aSize )
{
	long long result{ aInitialPos };
	result += aNumber;
	if( result < 0 )
		result = result % static_cast< long long >( aSize ) + aSize;
	else
		result = result % aSize;
	return static_cast< int >( result );
}

void Rearrange( std::list<long long>& aNumbers, const unsigned int& aN )
{
	std::list<int> moved( aNumbers.size(), 0 );
	std::iota( moved.begin(), moved.end(), 0 );

	for( unsigned int i = 0; i < aN; ++i )
	{
		for( auto movedIndex = 0; movedIndex < moved.size(); ++movedIndex )
		{
			const auto& movedIt = std::ranges::find( moved, movedIndex );
			const auto& numberIt = std::next( aNumbers.begin(), std::distance( moved.begin(), movedIt ) );
			const auto& currentPos = static_cast< int >( std::distance( aNumbers.begin(), numberIt ) );
			const auto& destination = CalculateDestination( *numberIt, currentPos, aNumbers.size() - 1 );

			if( currentPos != destination )
			{
				//Perform extraction
				std::list<long long> tmp;
				std::list<int> tmp2;
				tmp.splice( tmp.cbegin(), aNumbers, numberIt );
				tmp2.splice( tmp2.cbegin(), moved, movedIt );
				aNumbers.splice( std::next( aNumbers.begin(), destination ), tmp );
				moved.splice( std::next( moved.begin(), destination ), tmp2 );
			}
		}
	}
}