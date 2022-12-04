#pragma once

#include <istream>

class CRange
{
public:
	friend std::istream& operator>>( std::istream& aInput, CRange& aRange );

	const unsigned int& GetLowBound() const;
	const unsigned int& GetHighBound() const;

	bool Contains( const CRange& aOther ) const;
	bool Overlaps( const CRange& aOther ) const;

private:
	unsigned int mLowBound = 0;
	unsigned int mHighBound = 0;
};