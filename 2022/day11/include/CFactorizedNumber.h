#pragma once

#include <istream>
#include <ostream>
#include <list>

class CFactorizedNumber
{
public:
	using components = std::list<unsigned int>;

	explicit CFactorizedNumber( unsigned int aNumber );
	explicit CFactorizedNumber( const components& aComponents );

	friend std::istream& operator>>( std::istream& aInput, CFactorizedNumber& aFactorizedNumber );
	friend std::ostream& operator<<( std::ostream& aOutput, const CFactorizedNumber& aFactorizedNumber );
	friend CFactorizedNumber operator+( const CFactorizedNumber& aLHS, const CFactorizedNumber& aRHS );
	friend CFactorizedNumber operator*( const CFactorizedNumber& aLHS, const CFactorizedNumber& aRHS );
	friend CFactorizedNumber operator/( const CFactorizedNumber& aLHS, const unsigned int& aRHS );
	friend unsigned int operator%( const CFactorizedNumber& aLHS, const unsigned int& aRHS );

	std::size_t GetSize() const;

private:
	components mComponents;
};
