#pragma once

#include <istream>

class CElf
{
public:
	friend std::istream& operator>>( std::istream& aInput, CElf& aElf );

	const unsigned long& GetCalories() const;
private:
	unsigned long mCalories = 0;
};