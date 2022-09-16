#include "CDigit.h"

#include <string>

std::istream& operator>>( std::istream& aInput, CDigit& aDisplay )
{
	std::string digitString;
	aInput >> digitString;
	for( const auto& segment : digitString )
		aDisplay.mDigit.emplace( segment );
	return aInput;
}

const CDigit::digit& CDigit::GetDigit() const
{
	return mDigit;
}

bool CDigit::IsUnique() const
{
	const auto& size = mDigit.size();
	return size == 2 || size == 4 || size == 3 || size == 7;
}
