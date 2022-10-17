#include "CScanner.h"

#include "CCubeRotations.h"

#include <string>

namespace
{

CScanner::position operator-( const CScanner::position& aLHS, const CScanner::position& aRHS );
CScanner::position operator+( const CScanner::position& aLHS, const CScanner::position& aRHS );
CScanner::beacons Offset( const CScanner::beacons& aBeacons, CScanner::position aOffset );
unsigned int CountMatchingBeacons( const CScanner::beacons& aLHS, const CScanner::beacons& aRHS );

}

std::istream& operator>>( std::istream& aInput, CScanner& aScanner )
{
	std::string rawLine;
	std::getline( aInput, rawLine );
	std::getline( aInput, rawLine );

	while( !rawLine.empty() )
	{
		CBeacon beacon{ rawLine };
		aScanner.mBeacons.insert( std::move( beacon ) );
		rawLine.clear();
		std::getline( aInput, rawLine );
	}
	return aInput;
}

CScanner::beacons CScanner::Rotate( std::size_t aRotationIndex ) const
{
	CScanner::beacons result;

	for( const auto& beacon : mBeacons )
		result.emplace( beacon.Rotate( aRotationIndex ) );

	return result;
}

CScanner::beacons CScanner::InverseRotate( std::size_t aRotationIndex ) const
{
	CScanner::beacons result;

	for( const auto& beacon : mBeacons )
		result.emplace( beacon.InverseRotate( aRotationIndex ) );

	return result;
}

const CScanner::beacons& CScanner::GetBeacons() const
{
	return mBeacons;
}

CScanner::optional_position_rotation CScanner::RelativePosition( const CScanner& aRHS )const
{
	for( std::size_t rotationIndex = 0; rotationIndex < 24; ++rotationIndex )
	{
		const auto& relativePosition = RelativePosition( aRHS.Rotate( rotationIndex ) );
		if( relativePosition )
			return std::make_pair( *relativePosition, rotationIndex );
	}
	return {};
}

CScanner::optional_position CScanner::RelativePosition( const beacons& aBeacons ) const
{
	// Try every pair
	for( const auto& beaconLHS : mBeacons )
	{
		for( const auto& beaconRHS : aBeacons )
		{
			const auto& offset = beaconLHS.GetPosition() - beaconRHS.GetPosition();
			const auto& offsetBeacons = Offset( aBeacons, offset );
			const auto& countMatches = CountMatchingBeacons( mBeacons, offsetBeacons );
			if( countMatches >= 12 )
				return offset;
		}
	}
	return {};
}

namespace
{

CScanner::position operator-( const CScanner::position& aLHS, const CScanner::position& aRHS )
{
	CScanner::position result;

	for( unsigned int index = 0; index < aLHS.size(); ++index )
		result[ index ] = aLHS[ index ] - aRHS[ index ];

	return result;
}

CScanner::position operator+( const CScanner::position& aLHS, const CScanner::position& aRHS )
{
	CScanner::position result;

	for( unsigned int index = 0; index < aLHS.size(); ++index )
		result[ index ] = aLHS[ index ] + aRHS[ index ];

	return result;
}

CScanner::beacons Offset( const CScanner::beacons& aBeacons, CScanner::position aOffset )
{
	CScanner::beacons result;

	for( const auto& beacon : aBeacons )
		result.emplace( beacon.GetPosition() + aOffset );

	return result;
}

unsigned int CountMatchingBeacons( const CScanner::beacons& aLHS, const CScanner::beacons& aRHS )
{
	unsigned int result{ 0 };

	for( const auto& beacon : aLHS )
		if( aRHS.contains( beacon ) )
			++result;

	return result;
}

}