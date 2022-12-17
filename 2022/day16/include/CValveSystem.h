#pragma once

#include <istream>
#include <vector>

#include "CValve.h"

class CValveSystem
{
public:
	using valves = std::vector<CValve>;
	using target_valves_vector = std::vector<std::vector<unsigned int>>;

	friend std::istream& operator>>( std::istream& aInput, CValveSystem& aValveSystem );

	const valves& GetValves() const;
	std::size_t MaxReleasedPressure( const unsigned int& aMinutes, const unsigned short& aElephantCount = 0 ) const;

private:
	valves mValves;
	target_valves_vector mTargetValvesVector;
	unsigned int mCountRelevantValves;
};