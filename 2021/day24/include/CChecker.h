#ifndef C_CHECKER_H
#define C_CHECKER_H

#include <list>
#include <map>

#include "CInstruction.h"
#include "CModelNumber.h"

class CChecker
{
public:
	using alus = std::map<CAlu, CModelNumber>;
	using instructions = std::list<CInstruction>;

	CChecker();

	void Check( const instructions& aInstructions, const bool aKeepMax = true );

	CModelNumber GetMaximumValidNumber() const;
	CModelNumber GetMinimumValidNumber() const;

private:
	alus mAlus;
};

#endif // C_CHECKER_H