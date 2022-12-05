#pragma once

#include <istream>

class CCraneInstruction
{
public:
	using crane_move = std::pair<unsigned int, unsigned int>;

	friend std::istream& operator>>( std::istream& aInput, CCraneInstruction& aCraneInstruction );

	const unsigned int& GetCrateCount() const;
	const crane_move& GetCraneMove() const;

private:
	unsigned int mCrateCount;
	crane_move mCraneMove;
};