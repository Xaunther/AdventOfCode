#include "CBlizzard.h"

#include "CoordinateUtils.h"

CBlizzard::CBlizzard( const coordinates& aLocation, const coordinates& aDirection ):
	mLocation( aLocation ),
	mDirection( aDirection )
{
}

const CBlizzard::coordinates& CBlizzard::GetLocation() const
{
	return mLocation;
}

void CBlizzard::Move( coordinates& aMapSize )
{
	mLocation = mLocation + aMapSize + mDirection;
	mLocation = mLocation % aMapSize;
}
