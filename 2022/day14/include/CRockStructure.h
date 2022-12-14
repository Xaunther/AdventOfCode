#pragma once

#include <istream>
#include <set>
#include <map>

class CRockStructure
{
public:
	// Map of {x-index, y-indexes}
	//Will be faster for searching I guess
	using rocks = std::map<unsigned short, std::set<unsigned short>>;

	friend std::istream& operator>>( std::istream& aInput, CRockStructure& aRockStructure );

	const rocks& GetRocks() const;

	unsigned int CountRocks() const;
	unsigned int FallingSand( const unsigned short aStartX, const unsigned short aStartY );

private:
	rocks mRocks;
};