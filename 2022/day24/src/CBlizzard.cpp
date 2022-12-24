#include "CBlizzard.h"

namespace
{

inline CBlizzard::coordinates operator+( const CBlizzard::coordinates& aLHS, const CBlizzard::coordinates& aRHS );

}

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
	mLocation.first = mLocation.first % aMapSize.first;
	mLocation.second = mLocation.second % aMapSize.second;
}

namespace
{

inline CBlizzard::coordinates operator+( const CBlizzard::coordinates& aLHS, const CBlizzard::coordinates& aRHS )
{
	return { aLHS.first + aRHS.first, aLHS.second + aRHS.second };
}

}