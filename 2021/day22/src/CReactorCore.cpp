#include "CReactorCore.h"

namespace
{

bool Overlap( const CReactorCore::ranges& aLHS, const CReactorCore::ranges& aRHS );
bool Overlap( const CReactorCore::ranges::value_type& aLHS, const CReactorCore::ranges::value_type& aRHS );
CReactorCore::ranges OverlapRange( const CReactorCore::ranges& aLHS, const CReactorCore::ranges& aRHS );
std::set<CReactorCore::ranges> ExtractOverlap( const CReactorCore::ranges& aRange, const CReactorCore::ranges& aOverlap );
std::set<CRebootStep::range> CreateSegments( const CReactorCore::ranges::value_type& aLHS, const CReactorCore::ranges::value_type& aRHS );

}

const CReactorCore::lit_ranges& CReactorCore::GetLitRanges() const
{
	return mLitRanges;
}

std::size_t CReactorCore::CountLitCubes() const
{
	std::size_t result{ 0 };
	for( const auto& litRange : mLitRanges )
		result += static_cast< std::size_t >( litRange[ 0 ].second - litRange[ 0 ].first + 1 ) * static_cast< std::size_t >( litRange[ 1 ].second - litRange[ 1 ].first + 1 ) * static_cast< std::size_t >( litRange[ 2 ].second - litRange[ 2 ].first + 1 );
	return result;
}


void CReactorCore::Initialize( const reboot_steps& aRebootSteps, const CRebootStep::range& aRangeX, const CRebootStep::range& aRangeY, const CRebootStep::range& aRangeZ )
{
	const CRebootStep::ranges consideredRange{ aRangeX, aRangeY, aRangeZ };
	mLitRanges.insert( OverlapRange( aRebootSteps.front().GetRanges(), consideredRange ) );
	auto rebootStepsIt = aRebootSteps.cbegin();
	for( std::advance( rebootStepsIt, 1 ); rebootStepsIt != aRebootSteps.cend(); ++rebootStepsIt )
	{
		lit_ranges resultRanges = mLitRanges;
		lit_ranges incomingRanges{ ( *rebootStepsIt ).GetRanges() };
		for( const auto& previousLitRange : mLitRanges )
		{
			lit_ranges resultIncomingRanges;
			for( const auto& rawIncomingRange : incomingRanges )
			{
				const auto& incomingRange = OverlapRange( rawIncomingRange, consideredRange );
				if( Overlap( previousLitRange, incomingRange ) )
				{
					const auto& overlap = OverlapRange( previousLitRange, incomingRange );
					if( ( *rebootStepsIt ).GetSwitch() )
						for( const auto& region : ExtractOverlap( incomingRange, overlap ) )
							resultIncomingRanges.insert( region );
					else
					{
						for( const auto& region : ExtractOverlap( previousLitRange, overlap ) )
							resultRanges.insert( region );
						resultRanges.erase( previousLitRange );
						resultIncomingRanges.insert( incomingRange );
					}
				}
				else
					resultIncomingRanges.insert( incomingRange );
			}
			std::swap( incomingRanges, resultIncomingRanges );
		}
		if( ( *rebootStepsIt ).GetSwitch() )
		{
			for( const auto& incomingRange : incomingRanges )
				if( Overlap( incomingRange, consideredRange ) )
					mLitRanges.insert( OverlapRange( incomingRange, consideredRange ) );
		}
		else
			std::swap( mLitRanges, resultRanges );
	}
}

void CReactorCore::Reboot( const reboot_steps& aRebootSteps )
{
	const CRebootStep::range range{ std::numeric_limits<CRebootStep::range::first_type>::min(), std::numeric_limits<CRebootStep::range::first_type>::max() };
	Initialize( aRebootSteps, range, range, range );
}

namespace
{

bool Overlap( const CReactorCore::ranges& aLHS, const CReactorCore::ranges& aRHS )
{
	for( std::size_t index = 0; index < aLHS.size(); ++index )
		if( !Overlap( aLHS[ index ], aRHS[ index ] ) )
			return false;
	return true;
}

bool Overlap( const CReactorCore::ranges::value_type& aLHS, const CReactorCore::ranges::value_type& aRHS )
{
	return !( aLHS.second < aRHS.first || aLHS.first > aRHS.second );
}

CReactorCore::ranges OverlapRange( const CReactorCore::ranges& aLHS, const CReactorCore::ranges& aRHS )
{
	CReactorCore::ranges result;

	for( std::size_t index = 0; index < aLHS.size(); ++index )
		result[ index ] = { std::max( aLHS[ index ].first, aRHS[ index ].first ), std::min( aLHS[ index ].second, aRHS[ index ].second ) };

	return result;
}

std::set<CReactorCore::ranges> ExtractOverlap( const CReactorCore::ranges& aRange, const CReactorCore::ranges& aOverlap )
{
	std::set<CReactorCore::ranges> result;

	const auto& xRanges = CreateSegments( aRange[ 0 ], aOverlap[ 0 ] );
	const auto& yRanges = CreateSegments( aRange[ 1 ], aOverlap[ 1 ] );
	const auto& zRanges = CreateSegments( aRange[ 2 ], aOverlap[ 2 ] );

	for( const auto& xRange : xRanges )
		for( const auto& yRange : yRanges )
			for( const auto& zRange : zRanges )
				result.insert( CReactorCore::ranges{ xRange, yRange, zRange } );
	result.erase( aOverlap );

	return result;
}

std::set<CRebootStep::range> CreateSegments( const CReactorCore::ranges::value_type& aLHS, const CReactorCore::ranges::value_type& aRHS )
{
	std::set<CRebootStep::range> result;

	if( aLHS.first < aRHS.first && aLHS.second >= aRHS.first && aLHS.second <= aRHS.second )
	{
		result.emplace( aLHS.first, aRHS.first - 1 );
		result.emplace( aRHS.first, aLHS.second );
	}
	else if( aLHS.first < aRHS.first && aLHS.second > aRHS.second )
	{
		result.emplace( aLHS.first, aRHS.first - 1 );
		result.emplace( aRHS );
		result.emplace( aRHS.second + 1, aLHS.second );
	}
	else if( aLHS.first >= aRHS.first && aLHS.first <= aRHS.second && aLHS.second > aRHS.second )
	{
		result.emplace( aLHS.first, aRHS.second );
		result.emplace( aRHS.second + 1, aLHS.second );
	}
	else
	{
		result.emplace( aLHS );
	}

	return result;
}

}