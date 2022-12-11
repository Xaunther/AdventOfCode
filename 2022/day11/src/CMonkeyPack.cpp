#include "CMonkeyPack.h"

#include <algorithm>
#include <iostream>
#include <ranges>

std::istream& operator>>( std::istream& aInput, CMonkeyPack& aMonkeyPack )
{
	aMonkeyPack.mMonkeys.clear();
	for( auto& monkey : std::ranges::istream_view<CMonkey>( aInput ) )
		aMonkeyPack.mMonkeys.push_back( std::move( monkey ) );
	aMonkeyPack.mMonkeyProduct = 1;
	for( const auto& monkey : aMonkeyPack.mMonkeys )
		aMonkeyPack.mMonkeyProduct *= monkey.GetDivisorTest();
	return aInput;
}

const CMonkeyPack::monkeys& CMonkeyPack::GetMonkeys() const
{
	return mMonkeys;
}

void CMonkeyPack::PlayTurn( const unsigned int& aRelieveFactor )
{
	for( auto& monkey : mMonkeys )
		for( const auto& thrownItem : monkey.PlayTurn( aRelieveFactor, mMonkeyProduct ) )
			mMonkeys[ thrownItem.second ].AddItem( thrownItem.first );
}

std::size_t CMonkeyPack::MonkeyBusinessLevel() const
{
	std::vector<unsigned int> processedItemsCounts;
	processedItemsCounts.reserve( mMonkeys.size() );
	for( const auto& monkey : mMonkeys )
		processedItemsCounts.push_back( monkey.GetInspectedItemsCount() );
	std::ranges::sort( processedItemsCounts, std::greater() );
	return static_cast< std::size_t >( processedItemsCounts[ 0 ] ) * static_cast< std::size_t >( processedItemsCounts[ 1 ] );
}