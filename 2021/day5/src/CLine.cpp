#include "CLine.h"

#include <string>

namespace
{

CLine::coordinates CreateCoordinates( const std::string& aInput );

} // anonymous namespace

CLine::CLine() :
	mStart( { 0, 0 } ),
	mEnd( { 0, 0 } )
{
}

std::istream& operator>>( std::istream& aInput, CLine& aLine )
{
	std::string input;
	aInput >> input;
	if( !input.empty() )
	{
		aLine.mStart = CreateCoordinates( input );
		aInput >> input; // Skip arrow
		aInput >> input;
		aLine.mEnd = CreateCoordinates( input );
	}
	return aInput;
}

const CLine::coordinates& CLine::GetStart() const
{
	return mStart;
}

const CLine::coordinates& CLine::GetEnd() const
{
	return mEnd;
}

bool CLine::IsStraight() const
{
	return IsHorizontal() || IsVertical();
}

CLine::segment CLine::CreateSegment( const bool aUseDiagonals ) const
{
	segment result;

	if( IsHorizontal() )
		for( auto x = std::min( mStart.first, mEnd.first ); x <= std::max( mStart.first, mEnd.first ); ++x )
			result.emplace_back( x, mStart.second );
	else if( IsVertical() )
		for( auto y = std::min( mStart.second, mEnd.second ); y <= std::max( mStart.second, mEnd.second ); ++y )
			result.emplace_back( mStart.first, y );
	else if( aUseDiagonals )
	{
		if( IsAscending() )
			for( auto x = std::min( mStart.first, mEnd.first ), y = std::min( mStart.second, mEnd.second );
				y <= std::max( mStart.second, mEnd.second ); ++x, ++y )
				result.emplace_back( x, y );
		else
			for( auto x = std::max( mStart.first, mEnd.first ), y = std::min( mStart.second, mEnd.second );
				y <= std::max( mStart.second, mEnd.second ); --x, ++y )
				result.emplace_back( x, y );
	}

	return result;
}

bool CLine::IsHorizontal() const
{
	return mStart.second == mEnd.second;
}

bool CLine::IsVertical() const
{
	return mStart.first == mEnd.first;
}

bool CLine::IsAscending() const
{
	return !IsStraight() && ( ( mStart.first < mEnd.first&& mStart.second < mEnd.second ) || ( mStart.first > mEnd.first && mStart.second > mEnd.second ) );
}

namespace
{

CLine::coordinates CreateCoordinates( const std::string& aInput )
{
	CLine::coordinates result;

	result.first = std::stoul( aInput.substr( 0, aInput.find( "," ) ) );
	result.second = std::stoul( aInput.substr( aInput.find( "," ) + 1 ) );

	return result;
}

} // anonymous namespace