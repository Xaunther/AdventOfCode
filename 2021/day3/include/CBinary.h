#ifndef C_BINARY_H
#define C_BINARY_H

#include <vector>
#include <iostream>

class CBinary
{
public:
	enum E_RATE
	{
		GAMMA = 0,
		EPSILON = 1
	};

	CBinary();
	CBinary( const std::vector<unsigned int>& aVectorSum, const size_t& aSumCount, const E_RATE& aRate );

	using binary_number = std::vector<bool>;

	friend std::istream& operator>>( std::istream& aInput, CBinary& aBinary );

	const binary_number& GetBinaryNumber() const;

	unsigned int CalculateDecimalNumber() const;

private:
	binary_number mBinaryNumber;
};

#endif // C_BINARY_H