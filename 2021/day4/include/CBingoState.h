#ifndef C_BINGO_STATE_H
#define C_BINGO_STATE_H

#include "CBallsState.h"
#include "CCardState.h"

#include "CBalls.h"

class CBingo;

class CBingoState
{
public:
	using cards_states = std::vector<CCardState>;
	using ball = CBalls::balls::value_type;

	CBingoState( const size_t& aCardCount );

	const CBallsState& GetBallsState() const;
	const cards_states& GetCardsStates() const;

	size_t PlayUntilBingo( const CBingo& aBingo );
	size_t PlayUntilLastBingo( const CBingo& aBingo );

private:
	const ball& DrawNextBall( const CBingo& aBingo );

	CBallsState mBallsState;
	cards_states mCardsStates;
};

#endif // C_BINGO_STATE_H