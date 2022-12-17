#include "CValveSystem.h"

#include <ranges>

std::istream& operator>>( std::istream& aInput, CValveSystem& aValveSystem )
{
	for( auto& valve : std::ranges::istream_view<CValve>( aInput ) )
		aValveSystem.mValves.push_back( std::move( valve ) );
	return aInput;
}

const CValveSystem::valves& CValveSystem::GetValves() const
{
	return mValves;
}