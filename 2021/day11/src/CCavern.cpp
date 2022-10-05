#include "CCavern.h"

#include <string>

CCavern::CCavern():
	mFlashes( 0 ),
	mTotalSteps( 0 )
{
}

std::istream& operator>>( std::istream& aInput, CCavern& aCavern )
{
	while( aInput )
	{
		std::string octopusString;
		aInput >> octopusString;
		if( octopusString.empty() )
			return aInput;

		std::vector<CCavern::octopus> octopusRow;
		octopusRow.reserve( octopusString.size() );
		for( const auto& octopus : octopusString )
			octopusRow.emplace_back( static_cast< CCavern::octopus >( octopus - 48 ) );
		aCavern.mOctopuses.emplace_back( std::move( octopusRow ) );
	}
	return aInput;
}

const CCavern::octopuses& CCavern::GetOctopuses() const
{
	return mOctopuses;
}

const size_t& CCavern::GetFlashes() const
{
	return mFlashes;
}

const size_t& CCavern::GetTotalSteps() const
{
	return mTotalSteps;
}

void CCavern::PerformSteps( const size_t& aSteps )
{
	for( size_t step = 0; step < aSteps; ++step )
	{
		IncreaseEnergy();
		Flash();
		ResetEnergy();
	}
	mTotalSteps += aSteps;
}

void CCavern::PerformStepsUntilSync()
{
	const auto& target = mOctopuses.size() * mOctopuses.front().size();
	size_t previousFlashes;
	do
	{
		previousFlashes = mFlashes;
		IncreaseEnergy();
		Flash();
		ResetEnergy();
		++mTotalSteps;
	} while( mFlashes - previousFlashes < target );
}

void CCavern::IncreaseEnergy()
{
	for( auto& octopusRow : mOctopuses )
		for( auto& octopus : octopusRow )
			++octopus;
}

void CCavern::Flash()
{
	octopus_positions flashedOctopuses;
	for( size_t rowIndex = 0; rowIndex < mOctopuses.size(); ++rowIndex )
		for( size_t colIndex = 0; colIndex < mOctopuses[ rowIndex ].size(); ++colIndex )
			if( mOctopuses[ rowIndex ][ colIndex ] > 9 && flashedOctopuses.emplace( rowIndex, colIndex ).second )
				Flash( rowIndex, colIndex, flashedOctopuses );
	mFlashes += flashedOctopuses.size();
}

void CCavern::Flash( const size_t& aRowIndex, const size_t& aColIndex, octopus_positions& aFlashedOctopuses )
{
	//Propagate above
	if( aRowIndex > 0 && ++mOctopuses[ aRowIndex - 1 ][ aColIndex ] > 9 && aFlashedOctopuses.emplace( aRowIndex - 1, aColIndex ).second )
		Flash( aRowIndex - 1, aColIndex, aFlashedOctopuses );
	//Propagate below
	if( aRowIndex < mOctopuses.size() - 1 && ++mOctopuses[ aRowIndex + 1 ][ aColIndex ] > 9 && aFlashedOctopuses.emplace( aRowIndex + 1, aColIndex ).second )
		Flash( aRowIndex + 1, aColIndex, aFlashedOctopuses );
	//Propagate left
	if( aColIndex > 0 && ++mOctopuses[ aRowIndex ][ aColIndex - 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex, aColIndex - 1 ).second )
		Flash( aRowIndex, aColIndex - 1, aFlashedOctopuses );
	//Propagate right
	if( aColIndex < mOctopuses[ aRowIndex ].size() - 1 && ++mOctopuses[ aRowIndex ][ aColIndex + 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex, aColIndex + 1 ).second )
		Flash( aRowIndex, aColIndex + 1, aFlashedOctopuses );
	//Propagate above left
	if( aRowIndex > 0 && aColIndex > 0 && ++mOctopuses[ aRowIndex - 1 ][ aColIndex - 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex - 1, aColIndex - 1 ).second )
		Flash( aRowIndex - 1, aColIndex - 1, aFlashedOctopuses );
	//Propagate above right
	if( aRowIndex > 0 && aColIndex < mOctopuses[ aRowIndex - 1 ].size() - 1 && ++mOctopuses[ aRowIndex - 1 ][ aColIndex + 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex - 1, aColIndex + 1 ).second )
		Flash( aRowIndex - 1, aColIndex + 1, aFlashedOctopuses );
	//Propagate below left
	if( aRowIndex < mOctopuses.size() - 1 && aColIndex > 0 && ++mOctopuses[ aRowIndex + 1 ][ aColIndex - 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex + 1, aColIndex - 1 ).second )
		Flash( aRowIndex + 1, aColIndex - 1, aFlashedOctopuses );
	//Propagate below right
	if( aRowIndex < mOctopuses.size() - 1 && aColIndex < mOctopuses[ aRowIndex + 1 ].size() - 1 && ++mOctopuses[ aRowIndex + 1 ][ aColIndex + 1 ] > 9 && aFlashedOctopuses.emplace( aRowIndex + 1, aColIndex + 1 ).second )
		Flash( aRowIndex + 1, aColIndex + 1, aFlashedOctopuses );
}

void CCavern::ResetEnergy()
{
	for( auto& octopusRow : mOctopuses )
		for( auto& octopus : octopusRow )
			if( octopus > 9 )
				octopus = 0;
}
