#pragma once

#include <istream>
#include <set>

class CElfFlock
{
public:
	using position = int;
	using coordinates = std::pair<position, position>;
	using coordinates_set = std::set<coordinates>;

	friend std::istream& operator>>( std::istream& aInput, CElfFlock& aElfFlock );

	const coordinates_set& GetElvesPositions() const;

private:
	coordinates_set mElvesPositions;
};