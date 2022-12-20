#pragma once

#include <array>
#include <istream>
#include <set>

class CObsidian
{
public:
	using position = std::array<short, 3>;
	using positions = std::set<position>;

	friend std::istream& operator>>( std::istream& aInput, CObsidian& aObsidian );

	const positions& GetPositions() const;

private:
	positions mCubes;
};