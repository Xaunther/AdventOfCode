#pragma once

#include <optional>
#include <vector>
#include <set>

class CElevationMap;

class CPathFinder
{
public:
	// Position - Minimum steps
	using paths = std::vector<std::optional<unsigned int>>;
	using latest_positions = std::set<unsigned int>;

	unsigned int FindShortestPath( const CElevationMap& aMap );

private:
	paths mPaths;
	latest_positions mLatestPositions;
};