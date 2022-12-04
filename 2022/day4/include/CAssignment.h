#pragma once

#include <istream>

#include "CRange.h"

class CAssignment
{
public:
	friend std::istream& operator>>( std::istream& aInput, CAssignment& aAssignment );

	const std::pair<CRange, CRange>& GetRangePair() const;

	bool IsContained() const;
	bool IsOverlapped() const;

private:
	std::pair<CRange, CRange> mRangePair;
};