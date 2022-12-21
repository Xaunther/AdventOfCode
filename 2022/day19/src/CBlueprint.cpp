#include "CBlueprint.h"

std::istream& operator>>( std::istream& aInput, CBlueprint& aBlueprint )
{
	std::string word;
	for( auto& cost : aBlueprint.mRobotCosts )
		cost.clear();
	aBlueprint.mRobotCosts[ 0 ].emplace_back( CBlueprint::EMaterials::ORE, 0 );
	aBlueprint.mRobotCosts[ 1 ].emplace_back( CBlueprint::EMaterials::ORE, 0 );
	aBlueprint.mRobotCosts[ 2 ].emplace_back( CBlueprint::EMaterials::ORE, 0 );
	aBlueprint.mRobotCosts[ 2 ].emplace_back( CBlueprint::EMaterials::CLAY, 0 );
	aBlueprint.mRobotCosts[ 3 ].emplace_back( CBlueprint::EMaterials::ORE, 0 );
	aBlueprint.mRobotCosts[ 3 ].emplace_back( CBlueprint::EMaterials::OBSIDIAN, 0 );
	return aInput >> word >> word >> word >> word >> word >> word >> aBlueprint.mRobotCosts[ 0 ][ 0 ].second
		>> word >> word >> word >> word >> word >> aBlueprint.mRobotCosts[ 1 ][ 0 ].second
		>> word >> word >> word >> word >> word >> aBlueprint.mRobotCosts[ 2 ][ 0 ].second
		>> word >> word >> aBlueprint.mRobotCosts[ 2 ][ 1 ].second >> word >> word >> word >> word >> word
		>> aBlueprint.mRobotCosts[ 3 ][ 0 ].second >> word >> word >> aBlueprint.mRobotCosts[ 3 ][ 1 ].second >> word;
}

const CBlueprint::robot_costs& CBlueprint::GetRobotCosts() const
{
	return mRobotCosts;
}