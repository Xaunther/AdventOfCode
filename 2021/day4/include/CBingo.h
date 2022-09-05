#ifndef C_BINGO_H
#define C_BINGO_H

#include "CCard.h"
#include "CBalls.h"

class CBingo
{
public:
	using cards = std::vector<CCard>;

	friend std::istream& operator>>( std::istream& aInput, CBingo& aBingo );

	const CBalls& GetBalls() const;
	const cards& GetCards() const;

private:
	CBalls mBalls;
	cards mCards;
};

#endif