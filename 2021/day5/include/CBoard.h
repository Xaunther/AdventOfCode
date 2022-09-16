#ifndef C_BOARD_H
#define C_BOARD_H

#include "CLine.h"

#include <map>

class CBoard
{
public:
	using board_count = std::map<CLine::coordinates, unsigned int>;

	const board_count& GetBoardCount() const;

	void PinLine( const CLine& aLine, const bool aUseDiagonals = false );

	unsigned int CountOverlaps() const;

private:
	board_count mBoardCount;
};

#endif // C_BOARD_H