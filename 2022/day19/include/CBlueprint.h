#pragma once

#include <array>
#include <istream>
#include <vector>

class CBlueprint
{
public:
	enum class EMaterials
	{
		ORE = 0,
		CLAY = 1,
		OBSIDIAN = 2,
		GEODE = 3
	};

	using robot_cost = std::vector<std::pair<EMaterials, unsigned int>>;
	using robot_costs = std::array<robot_cost, 4>;

	friend std::istream& operator>>( std::istream& aInput, CBlueprint& aBlueprint );

	const robot_costs& GetRobotCosts() const;

private:
	robot_costs mRobotCosts;
};