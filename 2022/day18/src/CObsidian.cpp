#include "CObsidian.h"

#include <ranges>
#include <sstream>

std::istream& operator>>( std::istream& aInput, CObsidian& aObsidian )
{
	aObsidian.mCubes.clear();
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		std::stringstream lineStream;
		lineStream << line;
		CObsidian::position cube;
		for( auto& position : cube )
		{
			char comma;
			lineStream >> position >> comma;
		}
		aObsidian.mCubes.insert( std::move( cube ) );
	}
	return aInput;
}

const CObsidian::positions& CObsidian::GetPositions() const
{
	return mCubes;
}
