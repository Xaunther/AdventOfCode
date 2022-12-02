#pragma once

#include <istream>

class CMatch
{

public:
	enum class EFigure
	{
		ROCK = 1,
		PAPER = 2,
		SCISSORS = 3
	};

	using figures = std::pair<EFigure, EFigure>;

	friend std::istream& operator>>( std::istream& aInput, CMatch& aMatch );

	const figures& GetFigures() const;

	unsigned long MyScore() const;

	static EFigure CharToFigure( const char& aChar );

private:
	figures mFigures;
};