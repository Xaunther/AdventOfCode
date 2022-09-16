#ifndef C_LINE_H
#define C_LINE_H

#include <utility>
#include <istream>
#include <list>

class CLine
{
public:
	using coordinates = std::pair<unsigned int, unsigned int>;
	using segment = std::list<coordinates>;

	CLine();

	friend std::istream& operator>>( std::istream& aInput, CLine& aLine );

	const coordinates& GetStart() const;
	const coordinates& GetEnd() const;

	bool IsStraight() const;

	segment CreateSegment( const bool aUseDiagonals = false ) const;

private:
	bool IsHorizontal() const;
	bool IsVertical() const;
	bool IsAscending() const;

private:
	coordinates mStart;
	coordinates mEnd;
};

#endif // C_LINE_H