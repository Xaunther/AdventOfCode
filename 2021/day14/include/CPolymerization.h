#ifndef C_POLYMERIZATION_H
#define C_POLYMERIZATION_H

#include <istream>
#include <list>

#include "CPolymer.h"
#include "CInsertionRules.h"

class CPolymerization
{
public:
	friend std::istream& operator>>( std::istream& aInput, CPolymerization& aPolymerization );

	const CPolymer& GetPolymer() const;
	const CInsertionRules& GetInsertionRules() const;

	void Polymerize( const unsigned int& aSteps );
	void Polymerize();

	CPolymer mPolymer;
	CInsertionRules mInsertionRules;
};

#endif // C_POLYMERIZATION_H