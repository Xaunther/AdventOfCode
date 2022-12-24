#pragma once

#include <istream>
#include <vector>

#include "CBlizzard.h"

class CValley
{
public:
	using coordinates = CBlizzard::coordinates;
	using blizzards = std::vector<CBlizzard>;

	friend std::istream& operator>>( std::istream& aInput, CValley& aValley );
	const blizzards& GetBlizzards() const;

	unsigned int Traverse();

private:
	blizzards mBlizzards;
	coordinates mSize;
	coordinates mStartPosition;
	coordinates mEndPosition;
};