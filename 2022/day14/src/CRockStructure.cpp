#include "CRockStructure.h"

#include <ranges>
#include <numeric>
#include <sstream>

namespace
{

void FillWithRocks( CRockStructure::rocks& aRocks, std::stringstream& aSS );
unsigned short CalculateFloorY( const CRockStructure::rocks& aRocks );

}

std::istream& operator>>( std::istream& aInput, CRockStructure& aRockStructure )
{
	aRockStructure.mRocks.clear();
	while( !aInput.eof() )
	{
		std::string inputLine;
		std::getline( aInput, inputLine );
		if( inputLine.empty() )
			break;
		std::stringstream ss;
		ss << inputLine;
		FillWithRocks( aRockStructure.mRocks, ss );
	}

	return aInput;
}

const CRockStructure::rocks& CRockStructure::GetRocks() const
{
	return mRocks;
}

unsigned int CRockStructure::CountRocks() const
{
	return std::accumulate( mRocks.cbegin(), mRocks.cend(), unsigned int{ 0 },
		[]( const unsigned int& aResult, const rocks::value_type& aRow ) { return aResult + static_cast< unsigned int >( aRow.second.size() ); } );
}

unsigned int CRockStructure::FallingInfiniteSand( const unsigned short aStartX, const unsigned short aStartY )
{


	unsigned int result{ 0 };
	auto xIt = mRocks.find( aStartX );
	auto yIt = ( *mRocks.begin() ).second.begin();
	auto x = aStartX;
	auto y = aStartY;

	//While the sand does not fall infinitely, let it fall
	while( xIt != mRocks.end() && ( yIt = ( *xIt ).second.upper_bound( y ) ) != ( *xIt ).second.end() )
	{
		//Maybe can go left?
		{
			auto prevX = std::prev( xIt, 1 );
			if( xIt == mRocks.begin() || ( *prevX ).first < x - 1 )
			{
				xIt = mRocks.end();
				continue;
			}
			else if( !( *prevX ).second.contains( *yIt ) )
			{
				--x;
				y = ( *yIt ) - 1;
				xIt = prevX;
				continue;
			}
		}
		//Or perhaps right?
		{
			auto nextX = std::next( xIt, 1 );
			if( nextX == mRocks.end() || ( *nextX ).first > x + 1 )
			{
				xIt = mRocks.end();
				continue;
			}
			else if( !( *nextX ).second.contains( *yIt ) )
			{
				++x;
				y = ( *yIt ) - 1;
				xIt = nextX;
				continue;
			}
		}
		//If neither, it rests. Press F
		{
			( *xIt ).second.insert( std::prev( yIt, 1 ), *yIt - 1 );
			xIt = mRocks.find( aStartX );
			yIt = ( *mRocks.begin() ).second.begin();
			x = aStartX;
			y = aStartY;
			++result;
		}
	}
	return result;
}

unsigned int CRockStructure::FallingFiniteSand( const unsigned short aStartX, const unsigned short aStartY )
{
	const auto& floorY = CalculateFloorY( mRocks );

	unsigned int result{ 0 };
	auto xIt = mRocks.find( aStartX );
	auto yIt = ( *mRocks.begin() ).second.begin();
	auto x = aStartX;
	auto y = aStartY;

	//While the sand does not fall infinitely, let it fall
	while( !mRocks.contains( aStartX ) || !mRocks.at( aStartX ).contains( aStartY ) )
	{
		yIt = ( *xIt ).second.upper_bound( y );
		if( yIt == ( *xIt ).second.end() )
		{
			( *xIt ).second.insert( static_cast< unsigned short >( floorY - 1 ) );
			xIt = mRocks.find( aStartX );
			x = aStartX;
			y = aStartY;
			++result;
			continue;
		}
		//Maybe can go left?
		{
			auto prevX = std::prev( xIt, 1 );
			//Reaches floor and rests
			if( xIt == mRocks.begin() || ( *prevX ).first < x - 1 )
			{
				mRocks.emplace( rocks::key_type{ static_cast< unsigned short >( ( *xIt ).first - 1 ) }, rocks::mapped_type{ static_cast< unsigned short >( floorY - 1 ) } ).first;
				xIt = mRocks.find( aStartX );
				x = aStartX;
				y = aStartY;
				++result;
				continue;
			}
			else if( !( *prevX ).second.contains( *yIt ) )
			{
				--x;
				y = ( *yIt ) - 1;
				xIt = prevX;
				continue;
			}
		}
		//Or perhaps right?
		{
			auto nextX = std::next( xIt, 1 );
			//Reaches floor and rests
			if( nextX == mRocks.end() || ( *nextX ).first > x + 1 )
			{
				mRocks.emplace( rocks::key_type{ static_cast< unsigned short >( ( *xIt ).first + 1 ) }, rocks::mapped_type{ static_cast< unsigned short >( floorY - 1 ) } ).first;
				xIt = mRocks.find( aStartX );
				x = aStartX;
				y = aStartY;
				++result;
				continue;
			}
			else if( !( *nextX ).second.contains( *yIt ) )
			{
				++x;
				y = ( *yIt ) - 1;
				xIt = nextX;
				continue;
			}
		}
		//If neither, it rests. Press F
		{
			( *xIt ).second.insert( std::prev( yIt, 1 ), *yIt - 1 );
			xIt = mRocks.find( aStartX );
			x = aStartX;
			y = aStartY;
			++result;
		}
	}
	return result;
}

namespace
{

void FillWithRocks( CRockStructure::rocks& aRocks, std::stringstream& aSS )
{
	unsigned short prevX;
	unsigned short prevY;
	std::string arrow;
	char comma;
	aSS >> prevX >> comma >> prevY >> arrow;
	while( !aSS.eof() )
	{
		unsigned short endX;
		unsigned short endY;
		aSS >> endX >> comma >> endY >> arrow;
		if( prevY == endY )
			for( unsigned short x = std::min( prevX, endX ); x <= std::max( prevX, endX ); ++x )
				aRocks[ x ].insert( endY );
		else
		{
			auto& xSet = aRocks[ prevX ];
			for( unsigned short y = std::min( prevY, endY ); y <= std::max( prevY, endY ); ++y )
				xSet.insert( y );
		}
		prevX = endX;
		prevY = endY;
	}
}

unsigned short CalculateFloorY( const CRockStructure::rocks& aRocks )
{
	unsigned short result{ 0 };
	for( const auto& col : aRocks )
		if( ( *col.second.crbegin() ) > result )
			result = ( *col.second.crbegin() );
	return result + 2;
}

}