#ifndef C_CAVERN_H
#define C_CAVERN_H

#include <istream>
#include <set>
#include <vector>

class CCavern
{
public:
	using octopus = unsigned short;
	using octopuses = std::vector<std::vector<octopus>>;
	using octopus_positions = std::set<std::pair<size_t, size_t>>;

	CCavern();

	friend std::istream& operator>>( std::istream& aInput, CCavern& aCavern );

	const octopuses& GetOctopuses() const;
	const size_t& GetFlashes() const;
	const size_t& GetTotalSteps() const;

	void PerformSteps( const size_t& aSteps = 1 );
	void PerformStepsUntilSync();

private:
	void IncreaseEnergy();
	void Flash();
	void Flash( const size_t& aRowIndex, const size_t& aColIndex, octopus_positions& aFlashedOctopuses );
	void ResetEnergy();

	octopuses mOctopuses;
	size_t mFlashes;
	size_t mTotalSteps;
};

#endif // C_CAVERN_H