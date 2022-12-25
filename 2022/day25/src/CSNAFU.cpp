#include "CSNAFU.h"

#include <iostream>
#include <map>

namespace
{

static const std::map<char, short>& CreateToNumberMap();
static const std::map<short, char>& CreateToCharMap();

}

CSNAFU::CSNAFU( const std::string& aDigits ):
	mDigits( aDigits )
{
}


std::istream& operator>>( std::istream& aInput, CSNAFU& aSNAFU )
{
	return aInput >> aSNAFU.mDigits;
}

std::ostream& operator<<( std::ostream& aOutput, const CSNAFU& aSNAFU )
{
	return aOutput << aSNAFU.mDigits;
}

CSNAFU operator+( const CSNAFU& aLHS, const CSNAFU& aRHS )
{
	CSNAFU result;
	result.mDigits.reserve( std::max( aLHS.mDigits.size(), aRHS.mDigits.size() ) + 1 );


	const auto& toChar = CreateToCharMap();
	const auto& toNumber = CreateToNumberMap();
	short remainder = 0;

	for( auto lhsIt = aLHS.mDigits.crbegin(), rhsIt = aRHS.mDigits.crbegin(); lhsIt != aLHS.mDigits.crend() || rhsIt != aRHS.mDigits.crend() || remainder != 0; )
	{
		const auto& lhsDigit = toNumber.at( lhsIt != aLHS.mDigits.crend() ? ( *lhsIt++ ) : '0' );
		const auto& rhsDigit = toNumber.at( rhsIt != aRHS.mDigits.crend() ? ( *rhsIt++ ) : '0' );
		short digitResult = remainder + lhsDigit + rhsDigit;
		remainder = 0;
		if( digitResult > ( *toChar.crbegin() ).first )
		{
			digitResult -= static_cast< short >( toNumber.size() );
			++remainder;
		}
		else if( digitResult < ( *toChar.cbegin() ).first )
		{
			digitResult += static_cast< short >( toNumber.size() );
			--remainder;
		}

		result.mDigits.insert( result.mDigits.begin(), toChar.at( digitResult ) );
	}


	return result;
}

const std::string& CSNAFU::GetDigits() const
{
	return mDigits;
}

namespace
{

static const std::map<char, short>& CreateToNumberMap()
{
	static std::map<char, short> result;

	result[ '=' ] = -2;
	result[ '-' ] = -1;
	result[ '0' ] = 0;
	result[ '1' ] = 1;
	result[ '2' ] = 2;

	return result;
}

static const std::map<short, char>& CreateToCharMap()
{
	static std::map<short, char> result;

	result[ -2 ] = '=';
	result[ -1 ] = '-';
	result[ 0 ] = '0';
	result[ 1 ] = '1';
	result[ 2 ] = '2';

	return result;
}

}