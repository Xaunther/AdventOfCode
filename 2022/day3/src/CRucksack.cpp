#include "CRucksack.h"
#include <iostream>

namespace
{

unsigned int CharToPriority( const char& aChar );

}

std::istream& operator>>( std::istream& aInput, CRucksack& aRucksack )
{
	aRucksack.mCompartments.first.clear();
	aRucksack.mCompartments.second.clear();
	std::string stringInput;
	aInput >> stringInput;
	for( unsigned int i = 0; i < stringInput.size() / 2; ++i )
	{
		++aRucksack.mCompartments.first[ CharToPriority( stringInput[ i ] ) ];
		++aRucksack.mCompartments.second[ CharToPriority( stringInput[ stringInput.size() / 2 + i ] ) ];
	}

	return aInput;
}

const CRucksack::compartments& CRucksack::GetCompartments() const
{
	return mCompartments;
}

unsigned int CRucksack::CalculatedRepeatedPriority() const
{
	for( const auto& firstPair : mCompartments.first )
		if( mCompartments.second.find( firstPair.first ) != mCompartments.second.cend() )
			return firstPair.first;
	return 0;
}

bool CRucksack::HasSymbolWithPriority( const unsigned int& aPriority ) const
{
	if( mCompartments.first.find( aPriority ) != mCompartments.first.cend()
		|| mCompartments.second.find( aPriority ) != mCompartments.second.cend() )
		return true;
	return false;
}

unsigned int CRucksack::CommonInTrio( const CRucksack& aFirst, const CRucksack& aSecond, const CRucksack& aThird )
{
	for( const auto& firstPair : aFirst.GetCompartments().first )
	{
		if( aSecond.HasSymbolWithPriority( firstPair.first ) && aThird.HasSymbolWithPriority( firstPair.first ) )
			return firstPair.first;
	}
	for( const auto& secondPair : aFirst.GetCompartments().second )
	{
		if( aSecond.HasSymbolWithPriority( secondPair.first ) && aThird.HasSymbolWithPriority( secondPair.first ) )
			return secondPair.first;
	}
	return 0;
}

namespace
{

unsigned int CharToPriority( const char& aChar )
{
	if( aChar >= 'A' && aChar < 'a' ) //Uppercase
		return static_cast< unsigned int >( aChar ) - 38u;
	else
		return static_cast< unsigned int >( aChar ) - 96u;
}

}