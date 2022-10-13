#ifndef C_POLYMER_H
#define C_POLYMER_H

#include <istream>
#include <map>

class CInsertionRules;

class CPolymer
{
public:
	using polymer = std::map<std::string, std::size_t>;
	using element_count = std::map<char, std::size_t>;

	friend std::istream& operator>>( std::istream& aInput, CPolymer& aPolymer );

	const polymer& GetPolymer() const;
	const std::size_t& GetMostCommonElementCount() const;
	const std::size_t& GetLeastCommonElementCount() const;

	void Polymerize( const CInsertionRules& aInsertionRules );

private:
	polymer mPolymer;
	element_count mElementCount;
};

#endif // C_POLYMER_H