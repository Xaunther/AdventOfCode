#ifndef C_MULTI_GAME_STATE_H
#define C_MULTI_GAME_STATE_H

#include <istream>
#include <optional>

#include "CAmphibodState.h"
#include "CBurrow.h"

class CMultiGameState
{
public:
	class CGameState
	{
	public:
		using amphibod_states = CAmphibodState::amphibod_states;
		using game_states = std::set<CGameState>;

		explicit CGameState( const amphibod_states& aAmphibodStates = {} );

		friend std::istream& operator>>( std::istream& aInput, CGameState& aGameState );
		friend bool operator<( const CGameState& aLHS, const CGameState& aRHS );

		const amphibod_states& GetAmphibodStates() const;

		bool IsFinished( const CBurrow& aBurrow ) const;
		CAmphibodState::energy EnergyUsed() const;
		game_states Play( const CBurrow& aBurrow ) const;

	private:
		amphibod_states mAmphibodStates;
	};

	using energy = CAmphibodState::energy;
	using game_states = CGameState::game_states;

	friend std::istream& operator>>( std::istream& aInput, CMultiGameState& aMultiGameState );

	const game_states& GetGameStates() const;
	const std::optional<energy>& GetMinimumEnergy() const;

	void Play( const CBurrow& aBurrow );

private:
	game_states mGameStates;
	std::optional<energy> mMinimumEnergy;
};

#endif // C_MULTI_GAME_STATE_H