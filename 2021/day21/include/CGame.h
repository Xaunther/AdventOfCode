#ifndef C_GAME_H
#define C_GAME_H

#include <map>

class ADie;

class CGame
{
public:
	class CPlayerState
	{
	public:
		using position = unsigned short;

		explicit CPlayerState( const position& aInitialPosition );

		const position& GetPosition() const;
		const std::size_t& GetScore() const;
		void AddScore( const std::size_t& aScore );
		void Move( const position& aCells, const position& aCellCount );

		friend bool operator<( const CPlayerState& aLHS, const CPlayerState& aRHS );

	private:
		position mPosition;
		std::size_t mScore;
	};

	using state = std::map<std::pair<CPlayerState, CPlayerState>, std::size_t>;
	using cell_count = CPlayerState::position;

	explicit CGame( const cell_count& aCellCount, const std::size_t& aTargetScore, const state& aGameState );

	const state& GetState() const;
	const cell_count& GetCellCount() const;
	std::size_t GetLowestScore() const;
	std::size_t GetMostWins() const;
	std::size_t CountUnfinished() const;

	void Play( ADie& aDie ) const;

private:
	cell_count mCellCount;
	std::size_t mTargetScore;
	mutable state mGameState;
};

#endif // C_GAME_H