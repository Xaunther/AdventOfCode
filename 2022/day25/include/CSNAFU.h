#pragma once

#include <istream>
#include <ostream>

class CSNAFU
{
public:
	explicit CSNAFU( const std::string& aDigits = "" );

	friend std::istream& operator>>( std::istream& aInput, CSNAFU& aSNAFU );
	friend std::ostream& operator<<( std::ostream& aOutput, const CSNAFU& aSNAFU );
	friend CSNAFU operator+( const CSNAFU& aLHS, const CSNAFU& aRHS );

	const std::string& GetDigits() const;

private:
	std::string mDigits;
};