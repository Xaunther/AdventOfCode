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

	std::size_t CalculateSurfaceArea( const positions& aTrappedAirPositions = {} ) const;
	std::size_t CalculateExternalSurfaceArea() const;

private:
	positions mCubes;
};