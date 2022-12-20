#include "CObsidian.h"

#include <map>
#include <ranges>
#include <sstream>

namespace
{

CObsidian::positions CalculateTrappedAir( const CObsidian::positions& aCubes );

}

std::istream& operator>>( std::istream& aInput, CObsidian& aObsidian )
{
	aObsidian.mCubes.clear();
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		std::stringstream lineStream;
		lineStream << line;
		CObsidian::position cube;
		for( auto& position : cube )
		{
			char comma;
			lineStream >> position >> comma;
		}
		aObsidian.mCubes.insert( std::move( cube ) );
	}
	return aInput;
}

const CObsidian::positions& CObsidian::GetPositions() const
{
	return mCubes;
}

std::size_t CObsidian::CalculateSurfaceArea( const positions& aTrappedAirPositions ) const
{
	std::size_t result{ 0 };
	for( const auto& cube : mCubes )
	{
		if( !mCubes.contains( position{ cube[ 0 ] + short{ 1 }, cube[ 1 ], cube[ 2 ] } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ] + short{ 1 }, cube[ 1 ], cube[ 2 ] } ) )
			++result;
		if( !mCubes.contains( position{ cube[ 0 ] - short{ 1 }, cube[ 1 ], cube[ 2 ] } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ] - short{ 1 }, cube[ 1 ], cube[ 2 ] } ) )
			++result;
		if( !mCubes.contains( position{ cube[ 0 ], cube[ 1 ] + short{ 1 }, cube[ 2 ] } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ], cube[ 1 ] + short{ 1 }, cube[ 2 ] } ) )
			++result;
		if( !mCubes.contains( position{ cube[ 0 ], cube[ 1 ] - short{ 1 }, cube[ 2 ] } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ], cube[ 1 ] - short{ 1 }, cube[ 2 ] } ) )
			++result;
		if( !mCubes.contains( position{ cube[ 0 ], cube[ 1 ], cube[ 2 ] + short{ 1 } } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ], cube[ 1 ], cube[ 2 ] + short{ 1 } } ) )
			++result;
		if( !mCubes.contains( position{ cube[ 0 ], cube[ 1 ], cube[ 2 ] - short{ 1 } } )
			&& !aTrappedAirPositions.contains( position{ cube[ 0 ], cube[ 1 ], cube[ 2 ] - short{ 1 } } ) )
			++result;
	}
	return result;
}

std::size_t CObsidian::CalculateExternalSurfaceArea() const
{
	return CalculateSurfaceArea( CalculateTrappedAir( mCubes ) );
}

namespace
{

CObsidian::positions CalculateTrappedAir( const CObsidian::positions& aCubes )
{
	CObsidian::positions result;

	auto GetMinMax = []( const CObsidian::positions& aCubes )
	{
		std::array<std::pair<CObsidian::position::value_type, CObsidian::position::value_type>, 3> result{ {
			{ ( *aCubes.cbegin() )[ 0 ], ( *aCubes.cbegin() )[ 0 ] },
			{ ( *aCubes.cbegin() )[ 1 ], ( *aCubes.cbegin() )[ 1 ] },
			{ ( *aCubes.cbegin() )[ 2 ], ( *aCubes.cbegin() )[ 2 ] }
			} };
		for( const auto& cube : aCubes )
		{
			result[ 0 ].first = std::min( result[ 0 ].first, cube[ 0 ] );
			result[ 0 ].second = std::max( result[ 0 ].second, cube[ 0 ] );
			result[ 1 ].first = std::min( result[ 1 ].first, cube[ 1 ] );
			result[ 1 ].second = std::max( result[ 1 ].second, cube[ 1 ] );
			result[ 2 ].first = std::min( result[ 2 ].first, cube[ 2 ] );
			result[ 2 ].second = std::max( result[ 2 ].second, cube[ 2 ] );
		}
		return result;
	};
	const auto& minMax = GetMinMax( aCubes );

	for( short x = minMax[ 0 ].first - 1; x <= minMax[ 0 ].second + 1; ++x )
		for( short y = minMax[ 1 ].first - 1; y <= minMax[ 1 ].second + 1; ++y )
			for( short z = minMax[ 2 ].first - 1; z <= minMax[ 2 ].second + 1; ++z )
				if( !aCubes.contains( { x, y, z } ) )
					result.emplace_hint( result.end(), CObsidian::position{ x, y, z } );

	CObsidian::positions outsideCandidates;
	outsideCandidates.insert( result.extract( result.cbegin() ) );
	do
	{
		CObsidian::positions newOutsideCandidates;
		for( const auto& outsideCandidate : outsideCandidates )
		{
			auto found = result.find( CObsidian::position{ outsideCandidate[ 0 ] + short{ 1 }, outsideCandidate[ 1 ], outsideCandidate[ 2 ] } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
			found = result.find( CObsidian::position{ outsideCandidate[ 0 ] - short{ 1 }, outsideCandidate[ 1 ], outsideCandidate[ 2 ] } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
			found = result.find( CObsidian::position{ outsideCandidate[ 0 ], outsideCandidate[ 1 ] + short{ 1 }, outsideCandidate[ 2 ] } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
			found = result.find( CObsidian::position{ outsideCandidate[ 0 ], outsideCandidate[ 1 ] - short{ 1 }, outsideCandidate[ 2 ] } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
			found = result.find( CObsidian::position{ outsideCandidate[ 0 ], outsideCandidate[ 1 ], outsideCandidate[ 2 ] + short{ 1 } } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
			found = result.find( CObsidian::position{ outsideCandidate[ 0 ], outsideCandidate[ 1 ], outsideCandidate[ 2 ] - short{ 1 } } );
			if( found != result.end() )
				newOutsideCandidates.insert( result.extract( found ) );
		}
		outsideCandidates = std::move( newOutsideCandidates );
	} while( !outsideCandidates.empty() );

	return result;
}

}