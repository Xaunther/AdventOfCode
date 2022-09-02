#include "CMovement.h"

CMovement::CMovement() :
	mDistance( 0 )
{
}

std::istream& operator>>( std::istream& aInput, CMovement& aMovement )
{
	aInput >> aMovement.mDirection;
	aInput >> aMovement.mDistance;
	return aInput;
}

const std::string& CMovement::GetDirection() const
{
	return mDirection;
}
const unsigned int& CMovement::GetDistance() const
{
	return mDistance;
}