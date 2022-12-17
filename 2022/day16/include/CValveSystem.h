#pragma once

#include <istream>

#include "CValve.h"

class CValveSystem
{
public:
	using valves = std::vector<CValve>;

	friend std::istream& operator>>( std::istream& aInput, CValveSystem& aValveSystem );

	const valves& GetValves() const;

private:
	valves mValves;
};