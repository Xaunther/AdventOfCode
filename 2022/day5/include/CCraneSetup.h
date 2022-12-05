#pragma once

#include <istream>
#include <list>
#include <vector>

#include "CCraneInstruction.h"

class CCraneSetup
{
public:
	using stack = std::list<char>;
	using stacks = std::vector<stack>;
	using crane_instructions = std::list<CCraneInstruction>;

	friend std::istream& operator>>( std::istream& aInput, CCraneSetup& aCraneSetup );

	const stacks& GetStacks() const;
	const crane_instructions& GetCraneInstructions() const;

	void ExecuteInstructions9000();
	void ExecuteInstructions9001();

private:
	stacks mStacks;
	crane_instructions mCraneInstructions;
};