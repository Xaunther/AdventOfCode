#ifndef C_AMPHIBOD_STATE_H
#define C_AMPHIBOD_STATE_H

#include <set>
#include <utility>

#include "CBurrow.h"

class CAmphibodState
{
public:
	using position = std::pair<unsigned short, unsigned short>;
	using energy = std::size_t;
	using amphibod_states = std::set<CAmphibodState>;

	enum class TYPE
	{
		AMBER,
		BRONZE,
		COPPER,
		DESERT
	};

	CAmphibodState( const TYPE& aType, const position& aPosition );
	CAmphibodState( const energy& aRequiredEnergy, const position& aPosition, const energy& aConsumedEnergy );

	friend bool operator<( const CAmphibodState& aLHS, const CAmphibodState& aRHS );

	const position& GetPosition() const;
	const energy& GetRequiredEnergy() const;
	const energy& GetConsumedEnergy() const;

	amphibod_states Play( const CBurrow& aBurrow, const amphibod_states& aOtherAmphibodStates ) const;

	static energy RequiredEnergy( const TYPE& aType );
	bool IsFinished( const amphibod_states& aOtherAmphibodStates, const CBurrow& aBurrow ) const;

private:
	position mPosition;
	const energy mRequiredEnergy;
	energy mConsumedEnergy = 0;
};

#endif // C_AMPHIBOD_STATE_H