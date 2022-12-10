#pragma once

#include <vector>

class CInstruction;

class CCPU
{
public:
	using cycles = std::vector<int>;

	const cycles& GetCycles() const;

	void PerformInstruction( const CInstruction& aInstruction );
	long SignalStrength( const unsigned int& aCycleNumber );

private:
	void AddValue( const int& aValue );

	cycles mCycles{ 1 };
};