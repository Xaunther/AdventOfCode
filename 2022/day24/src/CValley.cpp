#include "CValley.h"

#include <map>
#include <ranges>

namespace
{

static const std::map<char, CValley::coordinates>& CreateDirectionMap();

}

std::istream& operator>>( std::istream& aInput, CValley& aValley )
{
	std::vector<std::string> inputRows;
	for( const auto& rowInput : std::ranges::istream_view<std::string>( aInput ) )
		inputRows.push_back( rowInput );

	// Entrance
	aValley.mStartPosition = { -1, static_cast< int >( inputRows.front().find( '.' ) ) - 1 };

	// Middle
	for( int i = 1; i < inputRows.size() - 1; ++i )
		for( int j = 1; j < inputRows[ i ].size() - 1; ++j )
			if( inputRows[ i ][ j ] != '.' )
				aValley.mBlizzards.emplace_back( CValley::coordinates{ i - 1,j - 1 }, CreateDirectionMap().at( inputRows[ i ][ j ] ) );

	// Exit
	aValley.mEndPosition = { static_cast< int >( inputRows.size() ), static_cast< int >( inputRows.front().find( '.' ) ) - 1 };

	aValley.mSize.first = static_cast< int >( inputRows.size() - 2 );
	aValley.mSize.second = static_cast< int >( inputRows.front().size() - 2 );

	return aInput;
}

const CValley::blizzards& CValley::GetBlizzards() const
{
	return mBlizzards;
}

namespace
{

static const std::map<char, CValley::coordinates>& CreateDirectionMap()
{
	static std::map<char, CValley::coordinates> result;
	result.emplace( '<', CValley::coordinates{ 0,-1 } );
	result.emplace( '^', CValley::coordinates{ -1,0 } );
	result.emplace( '>', CValley::coordinates{ 0,1 } );
	result.emplace( 'v', CValley::coordinates{ 1,0 } );
	return result;
}

}