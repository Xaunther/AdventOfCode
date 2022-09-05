#ifndef C_CARD_H
#define C_CARD_H

#include <array>
#include <iostream>
#include <optional>

class CCard
{
public:
	using card_numbers = std::array<std::array<unsigned int, 5>, 5>;
	using position = std::pair<size_t, size_t>;
	using optional_position = std::optional<position>;

	friend std::istream& operator>>( std::istream& aInput, CCard& aCard );

	const card_numbers& GetNumbers() const;
	size_t GetColumnCount() const;
	size_t GetRowCount() const;
	optional_position FindNumber( const unsigned int& aNumber ) const;

private:
	card_numbers mNumbers;
};

#endif // C_CARD_H