#pragma once

#include <vector>

class ATetrisPiece
{
public:
	using position = std::pair<std::size_t, std::size_t>;
	using positions = std::vector<position>;

	explicit ATetrisPiece( const positions& aPositions );

	virtual ~ATetrisPiece() = default;

	const positions& GetPositions() const;

	virtual const std::size_t& GetLeftmostPosition() const = 0;
	virtual const std::size_t& GetRightmostPosition() const = 0;

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveUp( const std::size_t& aYCount );

	positions ProjectLeftPositions() const;
	positions ProjectRightPositions() const;
	positions ProjectDownPositions() const;

	void SetInitialPosition( const std::size_t& aFloor );

private:
	virtual positions CalculateInitialPosition( const std::size_t& aFloor ) const = 0;

private:
	positions mPositions;
};