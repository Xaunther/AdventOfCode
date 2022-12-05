#include "CCraneInstruction.h"

std::istream& operator>>( std::istream& aInput, CCraneInstruction& aCraneInstruction )
{
	std::string word;
	return aInput >> word >> aCraneInstruction.mCrateCount >> word >>
		aCraneInstruction.mCraneMove.first >> word >> aCraneInstruction.mCraneMove.second;
}

const unsigned int& CCraneInstruction::GetCrateCount() const
{
	return mCrateCount;
}

const CCraneInstruction::crane_move& CCraneInstruction::GetCraneMove() const
{
	return mCraneMove;
}