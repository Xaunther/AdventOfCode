#pragma once

#include <vector>
#include <set>

class CElevationMap;

class CPathFinder
{
public:
	using paths = std::vector<bool>;
	using latest_positions = std::set<unsigned int>;

	unsigned int FindShortestPath( const CElevationMap& aMap, const bool aAnyPath = false );

private:
	paths mPaths;
	latest_positions mLatestPositions;
};