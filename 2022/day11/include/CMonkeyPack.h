#pragma once

#include <istream>
#include <vector>

#include "CMonkey.h"

class CMonkeyPack
{
public:
	using monkeys = std::vector<CMonkey>;

	friend std::istream& operator>>( std::istream& aInput, CMonkeyPack& aMonkeyPack );

	const monkeys& GetMonkeys() const;

	void PlayTurn( const unsigned int& aRelieveFactor );

	std::size_t MonkeyBusinessLevel() const;

private:
	monkeys mMonkeys;
	unsigned int mMonkeyProduct{ 1 };
};