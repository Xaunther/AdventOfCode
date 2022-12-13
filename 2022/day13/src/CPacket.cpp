#include "CPacket.h"

#include <iostream>

CPacket::CPacket( std::string_view aPacketString )
{
	// The string begins with "[" and ends with "]"
	for( std::size_t stringIndex = 1; stringIndex < aPacketString.size() - 1; ++stringIndex )
	{
		if( aPacketString[ stringIndex ] == '[' ) //Find matching ']' and build subpacket
		{
			auto packetStringSize = aPacketString.find( ']', stringIndex ) - stringIndex + 1;
			mElements.emplace_back( CPacket{ aPacketString.substr( stringIndex, packetStringSize ) } );
		}
		else //Insert number
			mElements.emplace_back( static_cast< unsigned short >( aPacketString[ stringIndex ] ) );
	}
}

std::istream& operator>>( std::istream& aInput, CPacket& aPacket )
{
	std::string inputString;
	aInput >> inputString;
	if( !inputString.empty() )
		aPacket = CPacket{ inputString };
	return aInput;
}

bool operator<( const CPacket& aLHS, const CPacket& aRHS )
{
	return aLHS.mElements < aRHS.mElements;
}

bool operator<( const CPacket& aLHS, const unsigned short& aRHS )
{
	return aLHS.mElements < CPacket::elements{ aRHS };
}

bool operator<( const unsigned short& aLHS, CPacket& aRHS )
{
	return CPacket::elements{ aLHS } < aRHS.mElements;
}