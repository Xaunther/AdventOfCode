#include "CBeacon.h"

#include <string>

CBeacon::CBeacon( const std::string& aStringPosition )
{
	std::size_t commaPosition{ 0 };
	std::size_t prevCommaPosition{ 0 };
	commaPosition = aStringPosition.find( "," );
	mPosition[ 0 ] = std::stoi( aStringPosition.substr( 0, commaPosition ) );
	prevCommaPosition = commaPosition;
	commaPosition = aStringPosition.find( ",", prevCommaPosition + 1 );
	mPosition[ 1 ] = std::stoi( aStringPosition.substr( prevCommaPosition + 1, commaPosition ) );
	mPosition[ 2 ] = std::stoi( aStringPosition.substr( commaPosition + 1 ) );

}

CBeacon::CBeacon( const position& aPosition ):
	mPosition( aPosition )
{
}

bool CBeacon::operator<( const CBeacon& aLHS ) const
{
	return mPosition < aLHS.GetPosition();
}


CBeacon::position CBeacon::Rotate( std::size_t aRotationIndex ) const
{
	const auto& rotationMatrix = GenerateCubeRotations()[ aRotationIndex ];

	position result;

	for( std::size_t i = 0; i < rotationMatrix.size(); ++i )
	{
		result[ i ] = 0;
		for( std::size_t j = 0; j < rotationMatrix.size(); ++j )
			result[ i ] += rotationMatrix[ i ][ j ] * mPosition[ j ];
	}

	return result;
}

CBeacon::position CBeacon::InverseRotate( std::size_t aRotationIndex ) const
{
	const auto& rotationMatrix = GenerateCubeRotations()[ aRotationIndex ];

	position result;

	for( std::size_t i = 0; i < rotationMatrix.size(); ++i )
	{
		result[ i ] = 0;
		for( std::size_t j = 0; j < rotationMatrix.size(); ++j )
			result[ i ] += rotationMatrix[ j ][ i ] * mPosition[ j ];
	}

	return result;
}

const CBeacon::position& CBeacon::GetPosition() const
{
	return mPosition;
}