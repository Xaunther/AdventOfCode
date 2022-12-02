#pragma once

#include <istream>

#include "CMatch.h"

class CFixedMatch
{

public:
	enum class EOutcome
	{
		LOSE = 0,
		DRAW = 3,
		WIN = 6
	};

	using figures = std::pair<CMatch::EFigure, EOutcome>;

	friend std::istream& operator>>( std::istream& aInput, CFixedMatch& aFixedMatch );

	const figures& GetFigures() const;

	unsigned long MyScore() const;

	static EOutcome CharToOutcome( const char& aChar );

private:
	figures mFigures;
};