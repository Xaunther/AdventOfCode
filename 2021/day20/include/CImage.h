#ifndef C_IMAGE_H
#define C_IMAGE_H

#include <istream>
#include <set>

class CImage
{
public:
	using lit_pixels = std::set<std::pair<int, int>>;
	using limits = std::pair<int, int>;

	CImage( std::istream& aInput );
	CImage( const lit_pixels& aLitPixels, const bool aInfinityLight = false );

	const lit_pixels& GetLitPixels() const;
	const limits& GetXLimits() const;
	const limits& GetYLimits() const;
	bool InfinityLight() const;

private:
	lit_pixels mLitPixels;
	limits mXLimits;
	limits mYLimits;
	bool mInfinityLight;
};

#endif // C_IMAGE_H