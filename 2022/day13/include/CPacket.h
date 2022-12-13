#pragma once

#include <istream>
#include <list>
#include <variant>

class CPacket
{
public:
	using element = std::variant<CPacket, unsigned short>;
	using elements = std::list<element>;

	explicit CPacket( std::string_view aPacketString );
	explicit CPacket() = default;
	explicit CPacket( const elements& aElements );
	friend std::istream& operator>>( std::istream& aInput, CPacket& aPacket );

	friend bool operator<( const CPacket& aLHS, const CPacket& aRHS );
	friend bool operator<( const CPacket& aLHS, const unsigned short& aRHS );
	friend bool operator<( const unsigned short& aLHS, const CPacket& aRHS );

private:
	elements mElements;
};