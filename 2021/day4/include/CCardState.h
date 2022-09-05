#ifndef C_CARD_STATE_H
#define C_CARD_STATE_H

#include <array>
#include <cstddef>

class CCard;

class CCardState
{
public:
	using marks = std::array<std::array<unsigned int, 5>, 5>;

	CCardState();

	const marks& GetMarks() const;

	void Mark( const size_t aRowIndex, const size_t aColIndex );
	bool HasBingo() const;
	size_t Score( const CCard& aCard, const unsigned int& aLastBall );

private:
	marks mMarks;
};

#endif