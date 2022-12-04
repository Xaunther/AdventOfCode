#include "CRange.h"

std::istream& operator>>( std::istream& aInput, CRange& aRange )
{
	char delimiter;
	return aInput >> aRange.mLowBound >> delimiter >> aRange.mHighBound;
}

const unsigned int& CRange::GetLowBound() const
{
	return mLowBound;
}

const unsigned int& CRange::GetHighBound() const
{
	return mHighBound;
}

bool CRange::Contains( const CRange& aOther ) const
{
	return mLowBound <= aOther.GetLowBound() && mHighBound >= aOther.GetHighBound();
}

bool CRange::Overlaps( const CRange& aOther ) const
{
	return !( mHighBound < aOther.GetLowBound() || mLowBound > aOther.GetHighBound() );
}
