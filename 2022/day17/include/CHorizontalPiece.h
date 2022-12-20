#pragma once

#include "ATetrisPiece.h"

class CHorizontalPiece: public ATetrisPiece
{
public:
	explicit CHorizontalPiece();

	const std::size_t& GetLeftmostPosition() const override;
	const std::size_t& GetRightmostPosition() const override;
	const std::size_t& GetTopPosition() const override;
	const std::size_t& GetBottomPosition() const override;

private:
	positions CalculateInitialPosition( const std::size_t& aFloor ) const override;
};