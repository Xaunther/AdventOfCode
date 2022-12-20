#pragma once

#include "ATetrisPiece.h"

class CCornerPiece: public ATetrisPiece
{
public:
	explicit CCornerPiece();

	const std::size_t& GetLeftmostPosition() const override;
	const std::size_t& GetRightmostPosition() const override;

private:
	positions CalculateInitialPosition( const std::size_t& aFloor ) const override;
};