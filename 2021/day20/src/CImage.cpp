#include "CImage.h"

namespace
{

CImage::lit_pixels CreateLitPixels( std::istream& aInput );
int GetMaxX( const CImage::lit_pixels& aLitPixels );
int GetMaxY( const CImage::lit_pixels& aLitPixels );
int GetMinX( const CImage::lit_pixels& aLitPixels );
int GetMinY( const CImage::lit_pixels& aLitPixels );

}

CImage::CImage( std::istream& aInput ):
	CImage( CreateLitPixels( aInput ) )
{
}

CImage::CImage( const lit_pixels& aLitPixels, const bool aInfinityLight ):
	mLitPixels( aLitPixels ),
	mXLimits( GetMinX( mLitPixels ), GetMaxX( mLitPixels ) ),
	mYLimits( GetMinY( mLitPixels ), GetMaxY( mLitPixels ) ),
	mInfinityLight( aInfinityLight )
{
}

const CImage::lit_pixels& CImage::GetLitPixels() const
{
	return mLitPixels;
}

const CImage::limits& CImage::GetXLimits() const
{
	return mXLimits;
}

const CImage::limits& CImage::GetYLimits() const
{
	return mYLimits;
}

bool CImage::InfinityLight() const
{
	return mInfinityLight;
}
namespace
{

CImage::lit_pixels CreateLitPixels( std::istream& aInput )
{
	CImage::lit_pixels result;

	CImage::lit_pixels::value_type::second_type yIndex{ 0 };
	while( true )
	{
		std::string rawString;
		aInput >> rawString;
		if( rawString.empty() )
			break;
		for( CImage::lit_pixels::value_type::first_type xIndex = 0; xIndex < rawString.size(); ++xIndex )
			if( rawString[ xIndex ] == '#' )
				result.emplace( xIndex, yIndex );
		++yIndex;
	}

	return result;
}

int GetMaxX( const CImage::lit_pixels& aLitPixels )
{
	return ( *aLitPixels.crbegin() ).first;
}

int GetMaxY( const CImage::lit_pixels& aLitPixels )
{
	int result{ 0 };

	for( const auto& litPixel : aLitPixels )
		result = std::max( result, litPixel.second );

	return result;
}

int GetMinX( const CImage::lit_pixels& aLitPixels )
{
	return ( *aLitPixels.cbegin() ).first;
}

int GetMinY( const CImage::lit_pixels& aLitPixels )
{
	int result{ 0 };

	for( const auto& litPixel : aLitPixels )
		result = std::min( result, litPixel.second );

	return result;
}


}