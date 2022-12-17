#pragma once

#include <istream>
#include <string>
#include <vector>

class CValve
{
public:
	using id_type = std::string;
	using target_valves = std::vector<id_type>;

	friend std::istream& operator>>( std::istream& aInput, CValve& aValve );

	const id_type& GetID() const;
	const unsigned int& GetFlowRate() const;
	const target_valves& GetTargetValves() const;

private:
	id_type mID;
	unsigned int mFlowRate;
	target_valves mTargetValves;
};