#ifndef C_CAVERN_PATHS_H
#define C_CAVERN_PATHS_H

#include "CCaverns.h"

#include <vector>

class CCavernPaths
{
public:
	using path = std::vector<CCaverns::cavern>;
	using paths = std::vector<path>;

	explicit CCavernPaths( const CCaverns::cavern_map& aCavernMap, bool aVisitSmallCavesOnce = true );

	const paths& GetPaths() const;

private:
	paths mPaths;
};

#endif // C_CAVERN_PATHS_H