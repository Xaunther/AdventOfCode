#include "CAssignment.h"

std::istream& operator>>( std::istream& aInput, CAssignment& aAssignment )
{
	char delimiter;
	return aInput >> aAssignment.mRangePair.first >> delimiter >> aAssignment.mRangePair.second;
}

const std::pair<CRange, CRange>& CAssignment::GetRangePair() const
{
	return mRangePair;
}

bool CAssignment::IsContained() const
{
	return mRangePair.first.Contains( mRangePair.second ) || mRangePair.second.Contains( mRangePair.first );
}

bool CAssignment::IsOverlapped() const
{
	return mRangePair.first.Overlaps( mRangePair.second );
}
