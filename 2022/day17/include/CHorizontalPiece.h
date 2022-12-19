#pragma once

#include "ATetrisPiece.h"

class CHorizontalPiece: public ATetrisPiece
{
public:
	explicit CHorizontalPiece();

	const std::size_t& GetLeftmostPosition() const override;
	const std::size_t& GetRightmostPosition() const override;

private:
	positions CalculateInitialPosition( const unsigned int& aFloor ) const override;
};