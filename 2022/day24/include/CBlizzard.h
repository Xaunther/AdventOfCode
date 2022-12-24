#pragma once

#include <istream>

class CBlizzard
{
public:
	using position = int;
	using coordinates = std::pair<position, position>;

	explicit CBlizzard( const coordinates& aLocation, const coordinates& aDirection );

	const coordinates& GetLocation() const;
	void Move( coordinates& aMapSize );

private:
	coordinates mLocation;
	coordinates mDirection;
};