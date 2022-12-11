#include "CMonkey.h"

namespace
{

std::istream& operator>>( std::istream& aInput, CMonkey::items& aItems );
std::istream& operator>>( std::istream& aInput, CMonkey::test_outcomes& aTestOutcomes );

}

std::istream& operator>>( std::istream& aInput, CMonkey& aMonkey )
{
	std::string inputString;
	aInput >> inputString;
	if( aInput.eof() )
		return aInput;
	return aInput >> inputString >> aMonkey.mItems >> aMonkey.mOperation >> inputString >> inputString >> inputString >> aMonkey.mDivisorTest >> aMonkey.mTestOutcomes;
}

const unsigned int& CMonkey::GetDivisorTest() const
{
	return mDivisorTest;
}

const unsigned int& CMonkey::GetInspectedItemsCount() const
{
	return mInspectedItemsCount;
}

CMonkey::throws CMonkey::PlayTurn( const unsigned int& aRelieveFactor, const unsigned int& aMonkeyProduct )
{
	throws result;
	result.reserve( mItems.size() );
	while( !mItems.empty() )
	{
		mItems.front() = mOperation( mItems.front() );
		mItems.front() /= aRelieveFactor;
		++mInspectedItemsCount;
		mItems.front() = mItems.front() % ( aRelieveFactor * aMonkeyProduct );
		result.emplace_back( mItems.front(), mItems.front() % mDivisorTest == 0 ? mTestOutcomes.first : mTestOutcomes.second );
		mItems.pop_front();
	}
	return result;
}

void CMonkey::AddItem( const std::size_t& aItem )
{
	mItems.push_back( aItem );
}

namespace
{

std::istream& operator>>( std::istream& aInput, CMonkey::items& aItems )
{
	std::string inputString;
	aInput >> inputString >> inputString;
	do
	{
		unsigned int item{ 1 };
		aInput >> item;
		aItems.emplace_back( item );
		aInput >> inputString;
	} while( inputString == "," );
	return aInput;
}

std::istream& operator>>( std::istream& aInput, CMonkey::test_outcomes& aTestOutcomes )
{
	std::string inputString;
	return aInput >> inputString >> inputString >> inputString >> inputString >> inputString >> aTestOutcomes.first >> inputString >> inputString >> inputString >> inputString >> inputString >> aTestOutcomes.second;
}

}