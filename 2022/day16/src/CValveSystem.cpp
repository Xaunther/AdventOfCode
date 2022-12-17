#include "CValveSystem.h"

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <ranges>
#include <iostream>

namespace
{

CValveSystem::target_valves_vector CreateTargetValvesVector( const CValveSystem::valves& aValves );

using current_valves = std::multiset<unsigned int>;
std::list<current_valves> DestinationValves( const current_valves& aCurrentValves, const CValveSystem::target_valves_vector& aTargetVakvesVector );

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

std::size_t CValveSystem::MaxReleasedPressure( const unsigned int& aMinutes, const unsigned short& aElephantCount ) const
{
	using opened_valves = std::set<unsigned int>;
	using current_valves = std::multiset<unsigned int>;
	using score = std::size_t;
	using state = std::pair<current_valves, opened_valves>;
	const auto& startValveIndex = static_cast< unsigned int >( std::distance( mValves.begin(),
		std::ranges::find_if( mValves, []( auto&& aValve ) { return aValve.GetID() == "AA"; } ) ) );
	current_valves startValveIndexes;
	for( unsigned short i = 0; i <= aElephantCount;++i )
		startValveIndexes.insert( startValveIndex );
	const auto initialState = state{ startValveIndexes, {} };
	std::map<state, std::pair<score, score>> result = { { initialState, {0,0} } };

	for( unsigned int minute = 0; minute < aMinutes - 4 * aElephantCount; ++minute )
	{
		std::cout << minute << std::endl;
		/*for( const auto& res : result )
		{
			std::cout << "Current valves (" << res.first.first.size() << "): ";
			for( const auto& v : res.first.first )
				std::cout << v << ", ";
			std::cout << std::endl << "Open valves: ";
			for( const auto& v : res.first.second )
				std::cout << v << ", ";
			std::cout << std::endl << "Score: " << res.second.first << std::endl;
			std::cout << "Rate: " << res.second.second << std::endl;
		}*/
		// Update release per minute
		for( auto& res : result )
			res.second.first += res.second.second;
		auto newResult = result;
		for( auto& res : result )
		{
			if( res.first.second.size() < mCountRelevantValves )
			{
				// Consider each possible destination
				const auto& destinationValvesList = DestinationValves( res.first.first, mTargetValvesVector );
				for( const auto& destinationValves : destinationValvesList )
				{
					auto newState = res.first;
					newState.first = destinationValves;
					auto newScore = res.second;
					for( auto destValveIt = destinationValves.cbegin(), initValveIt = res.first.first.cbegin(); destValveIt != destinationValves.cend(); ++destValveIt, ++initValveIt )
					{
						const auto& destValve = *destValveIt;
						if( destValve == *initValveIt && mValves[ destValve ].GetFlowRate() > 0 && !res.first.second.contains( destValve ) )
						{
							newState.second.insert( destValve );
							newScore.second += mValves[ destValve ].GetFlowRate();
						}
					}
					auto emplaced = newResult.emplace( std::move( newState ), newScore );
					if( !emplaced.second && res.second.first > ( *emplaced.first ).second.first )
						( *emplaced.first ).second.first = res.second.first;
				}
			}
			else if( res.first.first != startValveIndexes )
			{
				auto newState = res.first;
				newState.first = startValveIndexes;
				auto emplaced = newResult.emplace( std::move( newState ), res.second );
				if( !emplaced.second && res.second.first > ( *emplaced.first ).second.first )
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

std::list<current_valves> DestinationValves( const current_valves& aCurrentValves, const CValveSystem::target_valves_vector& aTargetVakvesVector )
{
	std::list<current_valves> result{ {} };
	for( const auto& currentValve : aCurrentValves )
	{
		std::list<current_valves> newResults;
		for( const auto& targetValve : aTargetVakvesVector[ currentValve ] )
		{
			for( const auto& res : result )
			{
				newResults.push_back( res );
				newResults.back().insert( targetValve );
			}
		}
		for( const auto& res : result )
		{
			newResults.push_back( res );
			newResults.back().insert( currentValve );
		}
		result = std::move( newResults );
	}
	return result;
}

}