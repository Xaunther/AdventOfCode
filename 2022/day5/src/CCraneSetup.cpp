#include "CCraneSetup.h"

#include <ranges>
#include <string>

std::istream& operator>>( std::istream& aInput, CCraneSetup& aCraneSetup )
{
	aCraneSetup = CCraneSetup{};
	std::string inputLine;
	std::getline( aInput, inputLine );
	while( inputLine[ 1 ] != '1' )
	{
		aCraneSetup.mStacks.resize( ( inputLine.size() + 1 ) / 4 );
		auto stackIt = aCraneSetup.mStacks.begin();
		for( auto charIndex = 1u; charIndex < inputLine.size(); charIndex += 4, ++stackIt )
			if( inputLine[ charIndex ] != ' ' )
				( *stackIt ).push_front( inputLine[ charIndex ] );
		std::getline( aInput, inputLine );
	}

	for( const auto& instruction : std::ranges::istream_view<CCraneInstruction>( aInput ) )
		aCraneSetup.mCraneInstructions.push_back( instruction );
	return aInput;
}

const CCraneSetup::stacks& CCraneSetup::GetStacks() const
{
	return mStacks;
}

const CCraneSetup::crane_instructions& CCraneSetup::GetCraneInstructions() const
{
	return mCraneInstructions;
}

void CCraneSetup::ExecuteInstructions9000()
{
	while( !mCraneInstructions.empty() )
	{
		for( unsigned int cratesMoved = 0; cratesMoved < mCraneInstructions.front().GetCrateCount(); ++cratesMoved )
		{
			mStacks[ mCraneInstructions.front().GetCraneMove().second - 1 ].push_back( mStacks[ mCraneInstructions.front().GetCraneMove().first - 1 ].back() );
			mStacks[ mCraneInstructions.front().GetCraneMove().first - 1 ].pop_back();
		}
		mCraneInstructions.pop_front();
	}
}

void CCraneSetup::ExecuteInstructions9001()
{
	while( !mCraneInstructions.empty() )
	{
		auto insertPosition = mStacks[ mCraneInstructions.front().GetCraneMove().second - 1 ].end();
		for( unsigned int cratesMoved = 0; cratesMoved < mCraneInstructions.front().GetCrateCount(); ++cratesMoved )
		{
			insertPosition = mStacks[ mCraneInstructions.front().GetCraneMove().second - 1 ].insert( insertPosition, mStacks[ mCraneInstructions.front().GetCraneMove().first - 1 ].back() );
			mStacks[ mCraneInstructions.front().GetCraneMove().first - 1 ].pop_back();
		}
		mCraneInstructions.pop_front();
	}
}