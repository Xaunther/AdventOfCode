#ifndef C_BEACON_H
#define C_BEACON_H

#include <string>

#include "CCubeRotations.h"

class CBeacon
{
public:
	using position = std::array<int, 3>;

	explicit CBeacon( const std::string& aStringPosition );
	explicit CBeacon( const position& aPosition );

	const position& GetPosition() const;

	bool operator<( const CBeacon& aLHS ) const;

	position Rotate( std::size_t aRotationIndex ) const;
	position InverseRotate( std::size_t aRotationIndex ) const;

private:
	position mPosition;
};

#endif // C_BEACON_H