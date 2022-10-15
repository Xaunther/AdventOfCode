#include "CTargetArea.h"

#include <string>

#include "CProjectile.h"

std::istream& operator>>( std::istream& aInput, CTargetArea& aTargetArea )
{
	std::string rawInput;
	aInput >> rawInput;
	aInput >> rawInput;
	aInput >> rawInput;
	aTargetArea.mRangeX.first = std::stoi( rawInput.substr( 2, rawInput.find( ".." ) ) );
	aTargetArea.mRangeX.second = std::stoi( rawInput.substr( rawInput.find( ".." ) + 2, rawInput.find( "," ) ) );
	aInput >> rawInput;
	aTargetArea.mRangeY.first = std::stoi( rawInput.substr( 2, rawInput.find( ".." ) ) );
	aTargetArea.mRangeY.second = std::stoi( rawInput.substr( rawInput.find( ".." ) + 2 ) );

	return aInput;
}

const CTargetArea::range& CTargetArea::GetRangeX() const
{
	return mRangeX;
}

const CTargetArea::range& CTargetArea::GetRangeY() const
{
	return mRangeY;
}

bool CTargetArea::IsInside( const CProjectile& aProjectile ) const
{
	return aProjectile.GetPosition().first >= mRangeX.first &&
		aProjectile.GetPosition().first <= mRangeX.second &&
		aProjectile.GetPosition().second >= mRangeY.first &&
		aProjectile.GetPosition().second <= mRangeY.second;
}
