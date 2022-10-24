#include "CModelNumber.h"

std::ostream& operator<<( std::ostream& aOutput, const CModelNumber& aModelNumber )
{
	for( const auto& digit : aModelNumber )
		aOutput << digit;
	return aOutput;
}
