#ifndef C_ALU_H
#define C_ALU_H

#include <array>

class CAlu
{
public:
	using numbers = std::array<int, 4>;

	enum class NUMBER
	{
		W = 0,
		X,
		Y,
		Z
	};

	CAlu();

	friend bool operator<( const CAlu& aLHS, const CAlu& aRHS );

	const int& GetNumber( const NUMBER& aNUMBER ) const;
	int& operator[]( const NUMBER& aNUMBER );

private:
	numbers mNumbers;
};

#endif // C_ALU_H