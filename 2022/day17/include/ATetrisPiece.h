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
	void MoveUp( const unsigned int& aYCount );

	positions ProjectLeftPositions() const;
	positions ProjectRightPositions() const;
	positions ProjectDownPositions() const;

	virtual void SetInitialPosition( const unsigned int& aFloor );

private:
	virtual positions CalculateInitialPosition( const unsigned int& aFloor ) const = 0;

private:
	positions mPositions;
};