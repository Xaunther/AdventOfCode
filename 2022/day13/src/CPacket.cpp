#include "CPacket.h"

#include <algorithm>
#include <string>

namespace
{

std::size_t FindClosingBracket( std::string_view aString, const std::size_t& aOffset );

}

CPacket::CPacket( std::string_view aPacketString )
{
	// The string begins with "[" and ends with "]"
	for( std::size_t stringIndex = 1; stringIndex < aPacketString.size() - 1; ++stringIndex )
	{
		if( aPacketString[ stringIndex ] == '[' ) //Find matching ']' and build subpacket
		{
			const auto& packetStringSize = FindClosingBracket( aPacketString, stringIndex + 1 ) - stringIndex + 1;
			mElements.emplace_back( CPacket{ aPacketString.substr( stringIndex, packetStringSize ) } );
			stringIndex += packetStringSize - 1;
		}
		else if( aPacketString[ stringIndex ] != ',' ) //Insert number
		{
			const auto& numberStringSize = aPacketString.find_first_of( ",]", stringIndex ) - stringIndex;
			mElements.emplace_back( static_cast< unsigned short >( std::stoul( aPacketString.substr( stringIndex, numberStringSize ).data() ) ) );
			stringIndex += numberStringSize - 1;
		}
	}
}

CPacket::CPacket( const elements& aElements ):
	mElements( aElements )
{
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
	return std::ranges::lexicographical_compare( aLHS.mElements, aRHS.mElements, []( auto&& aLHS, auto&& aRHS )
		{ return std::visit( [ &aRHS ]( auto&& aLHSArg ) { return std::visit( [ &aLHSArg ]( auto&& aRHSArg ) { return aLHSArg < aRHSArg; }, aRHS ); }, aLHS ); } );
}

bool operator<( const CPacket& aLHS, const unsigned short& aRHS )
{
	return aLHS < CPacket{ { aRHS } };
}

bool operator<( const unsigned short& aLHS, const CPacket& aRHS )
{
	return CPacket{ { aLHS } } < aRHS;
}

namespace
{

std::size_t FindClosingBracket( std::string_view aString, const std::size_t& aOffset )
{
	unsigned int depth = 0;
	for( std::size_t stringIndex = aOffset; stringIndex < aString.size() - 1; ++stringIndex )
	{
		if( aString[ stringIndex ] == '[' )
			++depth;
		else if( aString[ stringIndex ] == ']' )
		{
			if( depth == 0 )
				return stringIndex;
			else
				--depth;
		}
	}
	return std::string::npos;
}

}