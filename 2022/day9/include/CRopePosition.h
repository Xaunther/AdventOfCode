#pragma once

#include <set>
#include <utility>
#include <vector>

#include "CMove.h"

class CRopePosition
{
public:
	using position = std::pair<int, int>;
	using positions = std::vector<position>;
	using position_history = std::set<position>;

	explicit CRopePosition( const unsigned int& aKnotNumber );

	const positions& GetPositions() const;
	const position_history& GetTailHistory() const;

	void Move( const CMove& aMove );

private:
	void MoveHead( const CMove::EDirection& aDirection );
	void AdjustTailPositions();

	positions mKnotPositions;
	position_history mTailHistory = { { 0, 0 } };
};