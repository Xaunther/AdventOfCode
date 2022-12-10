#pragma once

#include <istream>

class CInstruction
{
public:
	enum class EType
	{
		NOOP,
		ADDX
	};

	friend std::istream& operator>>( std::istream& aInput, CInstruction& aInstruction );

	const EType& GetType() const;
	const int& GetValue() const;

private:
	EType mType;
	int mValue;
};