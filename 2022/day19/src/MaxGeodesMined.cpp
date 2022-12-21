#include "MaxGeodesMined.h"

#include "CBlueprint.h"

#include <algorithm>
#include <set>
#include <optional>
#include <ostream>
#include <map>

namespace
{

class CFactoryState
{
public:
	using materials_count = std::array<unsigned int, 4>;
	using robots_count = std::array<unsigned int, 4>;
	using newly_buyable = std::array<std::optional<bool>, 4>;

	friend std::ostream& operator<<( std::ostream& aOutput, const CFactoryState& aFactoryState );
	bool operator<( const CFactoryState& aOther ) const;

	const unsigned int& GetGeodeCount() const;
	const newly_buyable& GetNewlyBuyable() const;
	const robots_count& GetRobotsCount() const;

	void Work();
	void UpdateBuyables( const CBlueprint& aBlueprint );
	void BuyRobot( const CBlueprint::EMaterials& aType, const CBlueprint& aBlueprint );
	bool CanOpenMoreGeodes( const CBlueprint& aBluePrint ) const;

private:
	materials_count mMaterialsCount{ 0, 0, 0, 0 };
	robots_count mRobotsCount{ 1, 0, 0, 0 };

	std::optional<CBlueprint::EMaterials> mRobotInConstruction;
	newly_buyable mNewlyBuyable{ std::make_optional<bool>(), std::make_optional<bool>(), std::make_optional<bool>(), std::make_optional<bool>() };
};

}

unsigned int MaxGeodesMined( const CBlueprint& aBlueprint, const unsigned int& aMinutes )
{
	std::set<CFactoryState> states{ {} };
	std::map<CFactoryState::robots_count, unsigned int> robotHistory{ { ( *states.cbegin() ).GetRobotsCount(), 0 } };

	for( unsigned int minute = 0; minute < aMinutes; ++minute )
	{
		std::set<CFactoryState> newStates;
		for( auto& state : states )
		{
			// Try buying geode robot
			if( state.GetNewlyBuyable()[ 3 ].value_or( false ) )
			{
				auto newState = state;
				newState.BuyRobot( static_cast< CBlueprint::EMaterials >( 3 ), aBlueprint );
				newState.Work();
				newState.UpdateBuyables( aBlueprint );
				const auto& historyEmplaced = robotHistory.emplace( newState.GetRobotsCount(), minute + 1 );
				if( ( historyEmplaced.second || ( *historyEmplaced.first ).second == minute + 1 ) && newState.CanOpenMoreGeodes( aBlueprint ) )
					newStates.emplace( std::move( newState ) );
			}
			else
			{
				// Try without buying
				{
					auto newState = state;
					newState.Work();
					newState.UpdateBuyables( aBlueprint );
					if( newState.CanOpenMoreGeodes( aBlueprint ) )
						newStates.emplace( std::move( newState ) );
				}
				// Try buying each robot
				for( unsigned int robotIndex = 0; robotIndex < 3; ++robotIndex )
				{
					if( state.GetNewlyBuyable()[ robotIndex ].value_or( false ) )
					{
						auto newState = state;
						newState.BuyRobot( static_cast< CBlueprint::EMaterials >( robotIndex ), aBlueprint );
						newState.Work();
						newState.UpdateBuyables( aBlueprint );
						const auto& historyEmplaced = robotHistory.emplace( newState.GetRobotsCount(), minute + 1 );
						if( ( historyEmplaced.second || ( *historyEmplaced.first ).second == minute + 1 ) && newState.CanOpenMoreGeodes( aBlueprint ) )
							newStates.emplace( std::move( newState ) );
					}
				}
			}
		}
		states = std::move( newStates );
	}

	unsigned int result = 0;
	for( const auto& state : states )
		result = std::max( state.GetGeodeCount(), result );
	return result;
}

namespace
{

std::ostream& operator<<( std::ostream& aOutput, const CFactoryState& aFactoryState )
{
	aOutput << "Robot count: ";
	for( const auto& robot : aFactoryState.mRobotsCount )
		aOutput << robot << ", ";
	aOutput << std::endl;
	aOutput << "Material count: ";
	for( const auto& material : aFactoryState.mMaterialsCount )
		aOutput << material << ", ";
	return aOutput;
}

bool CFactoryState::operator<( const CFactoryState& aOther ) const
{
	if( mRobotsCount < aOther.mRobotsCount ) return true;
	if( mRobotsCount > aOther.mRobotsCount ) return false;
	return mMaterialsCount < aOther.mMaterialsCount;
}

const unsigned int& CFactoryState::GetGeodeCount() const
{
	return mMaterialsCount[ 3 ];
}

const CFactoryState::newly_buyable& CFactoryState::GetNewlyBuyable() const
{
	return mNewlyBuyable;
}

const CFactoryState::robots_count& CFactoryState::GetRobotsCount() const
{
	return mRobotsCount;
}

void CFactoryState::Work()
{
	for( unsigned int i = 0; i < mMaterialsCount.size(); ++i )
		mMaterialsCount[ i ] += mRobotsCount[ i ];
	if( mRobotInConstruction )
	{
		++mRobotsCount[ static_cast< unsigned int >( *mRobotInConstruction ) ];
		mRobotInConstruction.reset();
	}
}

void CFactoryState::UpdateBuyables( const CBlueprint& aBlueprint )
{
	auto EnoughMaterials = [ this, &aBlueprint ]( const unsigned int& aIndex )
	{
		return std::ranges::all_of( aBlueprint.GetRobotCosts()[ aIndex ], [ this ]( auto&& aRobotCost )
			{ return mMaterialsCount[ static_cast< unsigned int >( aRobotCost.first ) ] >= aRobotCost.second; } );
	};
	for( unsigned int buyableIndex = 0; buyableIndex < mNewlyBuyable.size(); ++buyableIndex )
	{
		if( EnoughMaterials( buyableIndex ) )
			mNewlyBuyable[ buyableIndex ] = !mNewlyBuyable[ buyableIndex ];
		else
			mNewlyBuyable[ buyableIndex ].reset();
	}
}

void CFactoryState::BuyRobot( const CBlueprint::EMaterials& aType, const CBlueprint& aBlueprint )
{
	mRobotInConstruction = aType;
	for( auto& buyable : mNewlyBuyable )
		buyable.reset();
	for( const auto& materialCost : aBlueprint.GetRobotCosts()[ static_cast< unsigned int >( aType ) ] )
		mMaterialsCount[ static_cast< unsigned int >( materialCost.first ) ] -= materialCost.second;
}

bool CFactoryState::CanOpenMoreGeodes( const CBlueprint& aBluePrint ) const
{
	if( mRobotsCount.back() > 0 ) return true;
	if( std::ranges::any_of( mNewlyBuyable, []( auto&& aBuyable ) { return aBuyable.value_or( false ); } ) ) return true;
	if( std::ranges::none_of( mNewlyBuyable, []( auto&& aBuyable ) { return aBuyable.value_or( true ); } ) ) return false;

	auto IsGathering = [ this, &aBluePrint ]( const unsigned int& aIndex )
	{
		for( const auto& cost : aBluePrint.GetRobotCosts()[ aIndex ] )
			if( mRobotsCount[ static_cast< unsigned int >( cost.first ) ] == 0 )
				return false;
		return true;
	};

	for( unsigned int i = 0; i < mRobotsCount.size(); ++i )
		if( !mNewlyBuyable[ i ] && IsGathering( i ) )
			return true;
	return false;
}

}