#ifndef C_LANTERNFISH_POPULATION
#define C_LANTERNFISH_POPULATION

#include <map>
#include <istream>

class CLanternfishPopulation
{
public:
	// Days left to reproduce - Number of lanternfish
	using population = std::map<unsigned int, unsigned long long>;

	friend std::istream& operator>>( std::istream& aInput, CLanternfishPopulation& aLanternfishPopulation );

	const population& GetPopulation() const;

	unsigned long long CountPopulation() const;

	void PassDay( const unsigned int& aDays );

private:
	void PassDay();

	population mPopulation;
};

#endif // C_LANTERNFISH_POPULATION