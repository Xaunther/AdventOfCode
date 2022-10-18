#ifndef C_FILTER_H
#define C_FILTER_H

#include <istream>
#include <set>

#include "CImage.h"

class CFilter
{
public:
	using lit_values = std::set<unsigned short>;

	CFilter( std::istream& aInput );

	const lit_values& GetLitValues() const;

	CImage ApplyFilter( const CImage& aImage ) const;
	bool SwitchesInfinityLight() const;

private:
	lit_values mLitValues;
	bool mSwitchesInfinityLight;
};

#endif // C_FILTER_H