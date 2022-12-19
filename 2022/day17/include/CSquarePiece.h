#pragma once

#include "ATetrisPiece.h"

class CSquarePiece: public ATetrisPiece
{
public:
	explicit CSquarePiece();

	const std::size_t& GetLeftmostPosition() const override;
	const std::size_t& GetRightmostPosition() const override;

private:
	positions CalculateInitialPosition( const unsigned int& aFloor ) const override;
};