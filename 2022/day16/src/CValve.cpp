#include "CValve.h"

#include <iostream>

std::istream& operator>>( std::istream& aInput, CValve& aValve )
{
	std::string word;
	char c;
	aValve.mTargetValves.clear();

	aInput >> word >> aValve.mID >> word >> word >> c >> c >> c >> c >> c >> aValve.mFlowRate >> word >> word >> word >> word >> word >> word;
	while( word.back() == ',' )
	{
		aValve.mTargetValves.push_back( word.substr( 0, word.size() - 1 ) );
		aInput >> word;
	}
	aValve.mTargetValves.push_back( word );
	return aInput;
}

const CValve::id_type& CValve::GetID() const
{
	return mID;
}

const unsigned int& CValve::GetFlowRate() const
{
	return mFlowRate;
}

const CValve::target_valves& CValve::GetTargetValves() const
{
	return mTargetValves;
}

unsigned int CValve::Release()
{
	unsigned int result = mFlowRate;
	mFlowRate = 0;
	return result;
}