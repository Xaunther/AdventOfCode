#include "CPolymerization.h"

std::istream& operator>>( std::istream& aInput, CPolymerization& aPolymerization )
{
	aInput >> aPolymerization.mPolymer;
	aInput >> aPolymerization.mInsertionRules;
	return aInput;
}

const CPolymer& CPolymerization::GetPolymer() const
{
	return mPolymer;
}

const CInsertionRules& CPolymerization::GetInsertionRules() const
{
	return mInsertionRules;
}

void CPolymerization::Polymerize( const unsigned int& aSteps )
{
	for( unsigned int step = 0; step < aSteps;++step )
		Polymerize();
}

void CPolymerization::Polymerize()
{
	mPolymer.Polymerize( mInsertionRules );
}
