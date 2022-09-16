#ifndef C_CRAB_ARMY_H
#define C_CRAB_ARMY_H

#include <vector>
#include <istream>

class CCrabArmy
{
public:
	using crabs = std::vector<unsigned int>;

	friend std::istream& operator>>( std::istream& aInput, CCrabArmy& aCrabArmy );

	const crabs& GetCrabs() const;

	unsigned long LeastAlignFuel();
	unsigned long LeastAlignFuel2() const;

private:
	crabs mCrabs;
};

#endif // C_CRAB_ARMY_H