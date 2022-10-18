#include "CFilter.h"

namespace
{

CFilter::lit_values CreateLitValues( std::istream& aInput );
CFilter::lit_values::value_type GetFilterIndex( const CImage& aImage, const CImage::limits::first_type& aX, const CImage::limits::first_type& aY );
bool IsOffLimits( const CImage::limits::first_type& aIndex, const CImage::limits& aLimits );

}

CFilter::CFilter( std::istream& aInput ):
	mLitValues( CreateLitValues( aInput ) ),
	mSwitchesInfinityLight( mLitValues.contains( 0 ) )
{
}

const CFilter::lit_values& CFilter::GetLitValues() const
{
	return mLitValues;
}

CImage CFilter::ApplyFilter( const CImage& aImage ) const
{
	CImage::lit_pixels litPixels;

	for( CImage::limits::second_type yIndex = aImage.GetYLimits().first - 1; yIndex <= aImage.GetYLimits().second + 1; ++yIndex )
		for( CImage::limits::first_type xIndex = aImage.GetXLimits().first - 1; xIndex <= aImage.GetXLimits().second + 1; ++xIndex )
			if( mLitValues.contains( GetFilterIndex( aImage, xIndex, yIndex ) ) )
				litPixels.emplace( xIndex, yIndex );
	return CImage{ std::move( litPixels ), mSwitchesInfinityLight ? !aImage.InfinityLight() : aImage.InfinityLight() };
}

bool CFilter::SwitchesInfinityLight() const
{
	return mSwitchesInfinityLight;
}

namespace
{

CFilter::lit_values CreateLitValues( std::istream& aInput )
{
	CFilter::lit_values result;

	std::string rawString;
	aInput >> rawString;
	for( CFilter::lit_values::value_type index = 0; index < rawString.size(); ++index )
		if( rawString[ index ] == '#' )
			result.emplace_hint( result.end(), index );

	return result;
}

CFilter::lit_values::value_type GetFilterIndex( const CImage& aImage, const CImage::limits::first_type& aX, const CImage::limits::first_type& aY )
{
	CFilter::lit_values::value_type result{ 0 };

	unsigned short power{ 8 };

	for( CImage::limits::second_type yIndex = aY - 1; yIndex <= aY + 1; ++yIndex )
		for( CImage::limits::first_type xIndex = aX - 1; xIndex <= aX + 1; ++xIndex, --power )
		{
			bool isLitPixel;
			if( aImage.GetLitPixels().contains( { xIndex, yIndex } ) ||
				( aImage.InfinityLight() && ( IsOffLimits( yIndex, aImage.GetYLimits() ) || IsOffLimits( xIndex, aImage.GetXLimits() ) ) ) )
				result += static_cast< CFilter::lit_values::value_type >( std::pow( 2, power ) );
		}

	return result;
}

bool IsOffLimits( const CImage::limits::first_type& aIndex, const CImage::limits& aLimits )
{
	return aIndex < aLimits.first || aIndex > aLimits.second;
}


}