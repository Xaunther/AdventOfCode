#include "CElfFlock.h"

#include <ranges>

std::istream& operator>>( std::istream& aInput, CElfFlock& aElfFlock )
{
	aElfFlock = CElfFlock{};
	std::size_t i = 0;
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		for( std::size_t j = 0; j < line.size(); ++j )
			if( line[ j ] == '#' )
				aElfFlock.mElvesPositions.emplace( static_cast< CElfFlock::position >( i ), static_cast< CElfFlock::position >( j ) );
		++i;
	}

	return aInput;
}

const CElfFlock::coordinates_set& CElfFlock::GetElvesPositions() const
{
	return mElvesPositions;
}