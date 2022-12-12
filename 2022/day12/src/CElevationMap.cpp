#include "CElevationMap.h"

#include <ranges>

std::istream& operator>>( std::istream& aInput, CElevationMap& aElevationMap )
{
	aElevationMap.mElevation.clear();
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		aElevationMap.mElevation.append( line );
		aElevationMap.mWidth = static_cast< unsigned int >( line.size() );
	}
	aElevationMap.mInitialPosition = static_cast< unsigned int >( aElevationMap.mElevation.find( 'S' ) );
	aElevationMap.mEndPosition = static_cast< unsigned int >( aElevationMap.mElevation.find( 'E' ) );
	aElevationMap.mElevation[ aElevationMap.mInitialPosition ] = 'a';
	aElevationMap.mElevation[ aElevationMap.mEndPosition ] = 'z';

	return aInput;
}

std::string_view CElevationMap::GetElevation() const
{
	return mElevation;
}

const unsigned int& CElevationMap::GetWidth() const
{
	return mWidth;
}

const unsigned int& CElevationMap::GetInitialPosition() const
{
	return mInitialPosition;
}

const unsigned int& CElevationMap::GetEndPosition() const
{
	return mEndPosition;
}
