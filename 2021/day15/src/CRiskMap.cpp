#include "CRiskMap.h"

std::istream& operator>>( std::istream& aInput, CRiskMap& aRiskMap )
{
	std::string stringRow;
	while( aInput >> stringRow )
	{
		CRiskMap::value_type riskRow;
		riskRow.reserve( stringRow.size() );
		for( const auto& stringNumber : stringRow )
			riskRow.push_back( static_cast< risk >( stringNumber - 48 ) );
		aRiskMap.push_back( std::move( riskRow ) );
	}
}