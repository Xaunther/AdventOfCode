#include "CDistressSignal.h"

std::istream& operator>>( std::istream& aInput, CDistressSignal& aDistressSignal )
{
	return aInput >> aDistressSignal.mPackets.first >> aDistressSignal.mPackets.second;
}

const CDistressSignal::packets& CDistressSignal::GetPackets() const
{
	return mPackets;
}

bool CDistressSignal::IsInOrder() const
{
	return mPackets.first < mPackets.second;
}