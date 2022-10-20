#include "CRebootStep.h"

#include <string>

namespace
{

CRebootStep::range CreateRange( const std::string& aStringRange );

}

std::istream& operator>>( std::istream& aInput, CRebootStep& aRebootStep )
{
	std::string stringInput;
	aInput >> stringInput;
	if( stringInput.empty() )
		return aInput;
	aRebootStep.mSwitch = stringInput == "on";
	aInput >> stringInput;
	std::size_t prevCommaFound = 0;
	std::size_t commaFound = stringInput.find( "," );
	aRebootStep.mRanges[ 0 ] = CreateRange( stringInput.substr( 0, commaFound ) );
	prevCommaFound = commaFound;
	commaFound = stringInput.find( ",", prevCommaFound + 1 );
	aRebootStep.mRanges[ 1 ] = CreateRange( stringInput.substr( prevCommaFound + 1, commaFound - prevCommaFound - 1 ) );
	aRebootStep.mRanges[ 2 ] = CreateRange( stringInput.substr( commaFound + 1 ) );

	return aInput;
}

const bool CRebootStep::GetSwitch() const
{
	return mSwitch;
}

const CRebootStep::ranges& CRebootStep::GetRanges() const
{
	return mRanges;
}

namespace
{

CRebootStep::range CreateRange( const std::string& aStringRange )
{
	CRebootStep::range result;

	result.first = std::stol( aStringRange.substr( 2, aStringRange.find( ".." ) ) );
	result.second = std::stol( aStringRange.substr( aStringRange.find( ".." ) + 2 ) );

	return result;
}

}