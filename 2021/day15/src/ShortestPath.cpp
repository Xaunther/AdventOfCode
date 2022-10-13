#include "ShortestPath.h"

#include <iostream>
#include <map>

using index = std::size_t;
using index_pair = std::pair<index, index>;
using vanguard_risk = std::map<index_pair, risk>;

namespace
{

risk CalculateRisk( const CRiskMap& aRiskMap, const index_pair& aIndexPair );
vanguard_risk MoveForward( vanguard_risk& aAccumulatedRisk, const vanguard_risk& aVanguardRisk, const CRiskMap& aRiskMap, const unsigned short& aRepetitions );

}

std::size_t ShortestPathRisk( const CRiskMap& aRiskMap, const unsigned short& aRepetitions )
{
	vanguard_risk vanguardRisk;
	vanguard_risk accumulatedRisk;
	vanguardRisk.emplace( index_pair{ 0, 0 }, risk{ 0 } );
	accumulatedRisk.emplace( index_pair{ 0, 0 }, risk{ 0 } );
	while( vanguardRisk.size() > 0 )
		vanguardRisk = MoveForward( accumulatedRisk, vanguardRisk, aRiskMap, aRepetitions );
	return ( *accumulatedRisk.crbegin() ).second;
}

namespace
{

risk CalculateRisk( const CRiskMap& aRiskMap, const index_pair& aIndexPair )
{
	index_pair tileCoordinates{ aIndexPair.first / aRiskMap.size(), aIndexPair.second / aRiskMap.front().size() };
	const auto& offset = static_cast< unsigned short >( tileCoordinates.first + tileCoordinates.second );

	risk result = ( aRiskMap[ aIndexPair.first % aRiskMap.size() ][ aIndexPair.second % aRiskMap.front().size() ] + offset ) % 9;
	return result != 0 ? result : 9;
}

vanguard_risk MoveForward( vanguard_risk& aAccumulatedRisk, const vanguard_risk& aVanguardRisk, const CRiskMap& aRiskMap, const unsigned short& aRepetitions )
{
	vanguard_risk result;

	auto AddRisk = [ & ]( const index_pair& aTargetIndexPair, const vanguard_risk::value_type& aVanguardRisk )
	{
		const risk& targetRisk = aVanguardRisk.second + CalculateRisk( aRiskMap, aTargetIndexPair );
		const auto& foundAccumulatedRisk = aAccumulatedRisk.find( aTargetIndexPair );
		if( foundAccumulatedRisk != aAccumulatedRisk.end() )
		{
			if( targetRisk < ( *foundAccumulatedRisk ).second )
			{
				( *foundAccumulatedRisk ).second = targetRisk;
				result.insert_or_assign( aTargetIndexPair, targetRisk );
			}
		}
		else
		{
			aAccumulatedRisk.emplace( aTargetIndexPair, targetRisk );
			result.emplace( aTargetIndexPair, targetRisk );
		}
	};

	for( const auto& vanguardRisk : aVanguardRisk )
	{
		//Step right
		if( vanguardRisk.first.second + 1 < aRiskMap[ vanguardRisk.first.first % aRiskMap.size() ].size() * aRepetitions )
			AddRisk( index_pair{ vanguardRisk.first.first, vanguardRisk.first.second + 1 }, vanguardRisk );
		//Step down
		if( vanguardRisk.first.first + 1 < aRiskMap.size() * aRepetitions )
			AddRisk( index_pair{ vanguardRisk.first.first + 1, vanguardRisk.first.second }, vanguardRisk );
		//Step left
		if( vanguardRisk.first.second > 0 )
			AddRisk( index_pair{ vanguardRisk.first.first, vanguardRisk.first.second - 1 }, vanguardRisk );
		//Step up
		if( vanguardRisk.first.first > 0 )
			AddRisk( index_pair{ vanguardRisk.first.first - 1, vanguardRisk.first.second }, vanguardRisk );
	}

	return result;
}

}