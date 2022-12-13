#pragma once

#include "CPacket.h"

class CDistressSignal
{
public:
	using packets = std::pair<CPacket, CPacket>;

	friend std::istream& operator>>( std::istream& aInput, CDistressSignal& aDistressSignal );

	const packets& GetPackets() const;

	bool IsInOrder() const;

private:
	packets mPackets;
};