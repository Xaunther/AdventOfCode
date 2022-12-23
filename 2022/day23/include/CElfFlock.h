#pragma once

#include <istream>
#include <optional>
#include <set>

class CElfFlock
{
public:
	using position = int;
	using coordinates = std::pair<position, position>;
	using coordinates_set = std::set<coordinates>;

	friend std::istream& operator>>( std::istream& aInput, CElfFlock& aElfFlock );

	const coordinates_set& GetElvesPositions() const;
	unsigned int Disperse( const std::optional<unsigned int>& aRounds = {} );
	std::size_t RectangleSize() const;

private:
	coordinates_set mElvesPositions;
};