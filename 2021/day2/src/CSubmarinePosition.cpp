#include "CSubmarinePosition.h"
#include "CMovement.h"

CSubmarinePosition::CSubmarinePosition() :
	mPosition( { 0,0 } ),
	mAim( 0 )
{
}

const CSubmarinePosition::position& CSubmarinePosition::GetPosition() const
{
	return mPosition;
}

const int& CSubmarinePosition::GetAim() const
{
	return mAim;
}

void CSubmarinePosition::Move( const CMovement& aMovement )
{
	if( aMovement.GetDirection() == "forward" )
		mPosition.first += aMovement.GetDistance();
	if( aMovement.GetDirection() == "up" )
		mPosition.second -= aMovement.GetDistance();
	else if( aMovement.GetDirection() == "down" )
		mPosition.second += aMovement.GetDistance();
}

void CSubmarinePosition::MoveWithAim( const CMovement& aMovement )
{
	if( aMovement.GetDirection() == "forward" )
	{
		mPosition.first += aMovement.GetDistance();
		mPosition.second += mAim * aMovement.GetDistance();
	}
	if( aMovement.GetDirection() == "up" )
		mAim -= aMovement.GetDistance();
	else if( aMovement.GetDirection() == "down" )
		mAim += aMovement.GetDistance();
}