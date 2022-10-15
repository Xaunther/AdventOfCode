#include "CProjectile.h"

CProjectile::CProjectile( const velocity& aVelocity ):
	mPosition( 0, 0 ),
	mVelocity( aVelocity )
{
}

const CProjectile::position CProjectile::GetPosition() const
{
	return mPosition;
}

const CProjectile::velocity CProjectile::GetVelocity() const
{
	return mVelocity;
}

void CProjectile::Move()
{
	mPosition.first += mVelocity.first;
	mPosition.second += mVelocity.second;

	if( mVelocity.first > 0 )
		--mVelocity.first;
	else if( mVelocity.first < 0 )
		++mVelocity.first;
	--mVelocity.second;
}