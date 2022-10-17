#include <iostream>
#include <map>
#include <set>
#include <string>

#include "year.h"
#include "day.h"

#include "CScanner.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

void Part1( const std::string& aFileName );

std::map<std::size_t, CScanner::optional_position_rotation::value_type> CalculateScannerPositions( const std::vector<CScanner>& aScanners );
std::map<std::size_t, CScanner::optional_position_rotation::value_type> RelativeToAbsolutePositions( std::map<std::pair<std::size_t, std::size_t>, CScanner::optional_position_rotation::value_type >& aRelativePositions, const std::size_t& aSize );

CScanner::position operator-( const CScanner::position& aLHS, const CScanner::position& aRHS );
CScanner::position operator+( const CScanner::position& aLHS, const CScanner::position& aRHS );

std::ostream& operator<<( std::ostream& aOutput, const CScanner::position& aPosition );

std::set<CBeacon::position> GetBeaconPositions( const std::vector<CScanner>& aScanners, const std::map<std::size_t, CScanner::optional_position_rotation::value_type>& aScannerPositionRotations );

}

int main()
{
	std::cout << "Example: ";
	Part1( EXAMPLE_FILE_NAME );
	std::cout << "Solution: ";
	Part1( INPUT_FILE_NAME );
	return 0;
}

namespace
{

void Part1( const std::string& aFileName )
{
	auto scanners = CreateVectorFromFile<CScanner>( aFileName );
	const auto& scannerPositions = CalculateScannerPositions( scanners );
	const auto& beaconPositions = GetBeaconPositions( scanners, scannerPositions );

	std::cout << beaconPositions.size() << ", ";

	int manhattanDistance{ 0 };
	for( const auto& scannerPositionLHS : scannerPositions )
		for( const auto& scannerPositionRHS : scannerPositions )
		{
			int thisDistance{ 0 };
			for( const auto& posComponent : ( scannerPositionLHS.second.first - scannerPositionRHS.second.first ) )
				thisDistance += std::abs( posComponent );
			manhattanDistance = std::max( manhattanDistance, thisDistance );
		}
	std::cout << manhattanDistance << std::endl;
}

std::map<std::size_t, CScanner::optional_position_rotation::value_type> CalculateScannerPositions( const std::vector<CScanner>& aScanners )
{
	std::map<std::pair<std::size_t, std::size_t>, CScanner::optional_position_rotation::value_type > relativePositions;

	for( auto LHSIt = aScanners.cbegin(); LHSIt != aScanners.cend(); ++LHSIt )
	{
		for( auto RHSIt = aScanners.cbegin(); RHSIt != aScanners.cend(); ++RHSIt )
		{
			const auto& result = ( *LHSIt ).RelativePosition( ( *RHSIt ) );
			if( result )
				//std::cout << "(" << std::distance( aScanners.cbegin(), LHSIt ) << "," << std::distance( aScanners.cbegin(), RHSIt ) << "): " << ( *result ).first << ", " << ( *result ).second << std::endl;
				relativePositions[ std::make_pair( static_cast< size_t >( std::distance( aScanners.cbegin(), LHSIt ) ), static_cast< size_t >( std::distance( aScanners.cbegin(), RHSIt ) ) ) ] = *result;
		}
	}
	return RelativeToAbsolutePositions( relativePositions, aScanners.size() );
}

std::map<std::size_t, CScanner::optional_position_rotation::value_type> RelativeToAbsolutePositions( std::map<std::pair<std::size_t, std::size_t>, CScanner::optional_position_rotation::value_type >& aRelativePositions, const std::size_t& aSize )
{
	std::map<std::size_t, CScanner::optional_position_rotation::value_type> result;
	result[ 0 ] = { CScanner::position{ 0, 0, 0 }, 0 };

	while( result.size() < aSize )
	{
		for( const auto& absolutePosition : result )
		{
			for( auto relPosIt = aRelativePositions.begin(); relPosIt != aRelativePositions.end(); )
			{
				if( ( *relPosIt ).first.first == absolutePosition.first )
				{
					const auto& rotatedPosition = CBeacon{ ( *relPosIt ).second.first }.InverseRotate( absolutePosition.second.second );
					result[ ( *relPosIt ).first.second ].first = absolutePosition.second.first + rotatedPosition;
					result[ ( *relPosIt ).first.second ].second = ComposeRotationIndexes( absolutePosition.second.second, InverseRotationIndex( ( *relPosIt ).second.second ) );
					relPosIt = aRelativePositions.erase( relPosIt );
				}
				else
					++relPosIt;
			}
		}
	}

	return result;
}

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

std::ostream& operator<<( std::ostream& aOutput, const CScanner::position& aPosition )
{
	aOutput << aPosition[ 0 ] << " " << aPosition[ 1 ] << " " << aPosition[ 2 ];
	return aOutput;
}

std::set<CBeacon::position> GetBeaconPositions( const std::vector<CScanner>& aScanners, const std::map<std::size_t, CScanner::optional_position_rotation::value_type>& aScannerPositionRotations )
{
	std::set<CBeacon::position> result;

	for( const auto& scannerPositionRotation : aScannerPositionRotations )
	{
		for( const auto& beacon : aScanners[ scannerPositionRotation.first ].InverseRotate( scannerPositionRotation.second.second ) )
			result.insert( beacon.GetPosition() + scannerPositionRotation.second.first );
	}

	return result;
}

}