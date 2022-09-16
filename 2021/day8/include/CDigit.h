#ifndef C_DIGIT_H
#define C_DIGIT_H

#include <set>
#include <array>
#include <istream>

class CDigit
{
public:
	using digit = std::set<char>;

	friend std::istream& operator>>( std::istream& aInput, CDigit& aDisplay );

	const digit& GetDigit() const;

	bool IsUnique() const;

private:
	digit mDigit;
};

#endif // C_DIGIT_H