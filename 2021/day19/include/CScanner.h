#ifndef C_SCANNER_H
#define C_SCANNER_H

#include <istream>
#include <optional>
#include <set>

#include "CBeacon.h"

class CScanner
{
public:
	using beacons = std::set<CBeacon>;
	using position = CBeacon::position;
	using optional_position = std::optional<position>;
	using optional_position_rotation = std::optional<std::pair<position, std::size_t>>;

	friend std::istream& operator>>( std::istream& aInput, CScanner& aScanner );

	const beacons& GetBeacons() const;

	beacons Rotate( std::size_t aRotationIndex ) const;
	beacons InverseRotate( std::size_t aRotationIndex ) const;

	optional_position_rotation RelativePosition( const CScanner& aRHS ) const;
	optional_position RelativePosition( const beacons& aBeacons ) const;

private:
	beacons mBeacons;
};

#endif // C_SCANNER_H