#include "CValveSystem.h"

#include <algorithm>
#include <map>
#include <set>
#include <ranges>
#include <iostream>

namespace
{

CValveSystem::target_valves_vector CreateTargetValvesVector( const CValveSystem::valves& aValves );

}

std::istream& operator>>( std::istream& aInput, CValveSystem& aValveSystem )
{
	for( auto& valve : std::ranges::istream_view<CValve>( aInput ) )
		aValveSystem.mValves.push_back( std::move( valve ) );
	aValveSystem.mTargetValvesVector = CreateTargetValvesVector( aValveSystem.mValves );
	aValveSystem.mCountRelevantValves = static_cast< unsigned int >( std::ranges::count_if(
		aValveSystem.mValves, []( auto&& aValve ) { return aValve.GetFlowRate() > 0; } ) );

	return aInput;
}

const CValveSystem::valves& CValveSystem::GetValves() const
{
	return mValves;
}

std::size_t CValveSystem::MaxReleasedPressure( const unsigned int& aMinutes ) const
{
	using opened_valves = std::set<unsigned int>;
	using current_valve = unsigned int;
	using score = std::size_t;
	using state = std::pair<current_valve, opened_valves>;
	const auto startValveIndex = static_cast< unsigned int >( std::distance( mValves.begin(),
		std::ranges::find_if( mValves, []( auto&& aValve ) { return aValve.GetID() == "AA"; } ) ) );
	const auto initialState = state{ startValveIndex, {} };
	std::map<state, std::pair<score, score>> result = { { initialState, {0,0} } };

	for( unsigned int minute = 0; minute < aMinutes; ++minute )
	{
		// Update release per minute
		for( auto& res : result )
			res.second.first += res.second.second;
		auto newResult = result;
		for( auto& res : result )
		{
			if( res.first.second.size() < mCountRelevantValves )
			{
				// Consider each possible destination
				for( const auto& destinationValve : mTargetValvesVector[ res.first.first ] )
				{
					auto newState = res.first;
					newState.first = destinationValve;
					auto emplaced = newResult.emplace( std::move( newState ), res.second );
					if( !emplaced.second )
						if( res.second.first > ( *emplaced.first ).second.first )
							( *emplaced.first ).second.first = res.second.first;
				}
				// Consider opening the current valve
				if( mValves[ res.first.first ].GetFlowRate() > 0 && !res.first.second.contains( res.first.first ) )
				{
					auto newState = res.first;
					newState.second.insert( res.first.first );
					auto newScore = res.second;
					newScore.second += mValves[ res.first.first ].GetFlowRate();
					auto emplaced = newResult.emplace( std::move( newState ), newScore );
					if( !emplaced.second )
						if( newScore.first > ( *emplaced.first ).second.first )
							( *emplaced.first ).second.first = newScore.first;
				}
				// Sit
				else
					newResult.emplace( res );
			}
			else if( res.first.first != startValveIndex )
			{
				auto newState = res.first;
				newState.first = startValveIndex;
				auto emplaced = newResult.emplace( std::move( newState ), res.second );
				if( !emplaced.second )
					if( res.second.first > ( *emplaced.first ).second.first )
						( *emplaced.first ).second.first = res.second.first;
			}
		}
		result = std::move( newResult );
	}

	std::size_t maxPressureReleased = 0;
	for( const auto& res : result )
		if( res.second.first > maxPressureReleased )
			maxPressureReleased = res.second.first;
	return maxPressureReleased;
}

namespace
{

CValveSystem::target_valves_vector CreateTargetValvesVector( const CValveSystem::valves& aValves )
{
	CValveSystem::target_valves_vector result;
	result.reserve( aValves.size() );

	for( const auto& valve : aValves )
	{
		CValveSystem::target_valves_vector::value_type targetValves;
		targetValves.reserve( valve.GetTargetValves().size() );
		for( const auto& targetValve : valve.GetTargetValves() )
			targetValves.push_back( static_cast< unsigned int >( std::distance( aValves.cbegin(),
				std::ranges::find_if( aValves, [ &targetValve ]( auto&& aValve ) { return targetValve == aValve.GetID(); } ) ) ) );
		result.push_back( std::move( targetValves ) );
	}

	return result;
}

}