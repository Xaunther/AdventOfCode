#pragma once

#include <istream>
#include <list>

class CSignal
{
public:
	using signal = std::list<char>;

	friend std::istream& operator>>( std::istream& aInput, CSignal& aSignal );

	const signal& GetSignal() const;

	unsigned int FindStartMarker( const unsigned int aMarkerSize ) const;

private:
	signal mSignal;
};