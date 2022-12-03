#pragma once

#include <istream>
#include <map>

class CRucksack
{
public:
	using compartment = std::map<unsigned int, unsigned int>;
	using compartments = std::pair<compartment, compartment>;
	friend std::istream& operator>>( std::istream& aInput, CRucksack& aRucksack );

	const compartments& GetCompartments() const;

	unsigned int CalculatedRepeatedPriority() const;

	bool HasSymbolWithPriority( const unsigned int& aPriority ) const;

	static unsigned int CommonInTrio( const CRucksack& aFirst, const CRucksack& aSecond, const CRucksack& aThird );
private:
	compartments mCompartments;
};