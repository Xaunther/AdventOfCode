#pragma once

#include "ATetrisPiece.h"

class CCornerPiece: public ATetrisPiece
{
public:
	explicit CCornerPiece();

	const std::size_t& GetLeftmostPosition() const override;
	const std::size_t& GetRightmostPosition() const override;
	const std::size_t& GetTopPosition() const override;
	const std::size_t& GetBottomPosition() const override;

	positions ProjectLeftPositions() const override;
	positions ProjectRightPositions() const override;
	positions ProjectDownPositions() const override;

private:
	positions CalculateInitialPosition( const std::size_t& aFloor ) const override;
};