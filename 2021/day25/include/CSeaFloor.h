#ifndef C_SEA_FLOOR_H
#define C_SEA_FLOOR_H

#include <istream>
#include <set>

class CSeaFloor
{
public:
	using sea_cucumber = std::pair<unsigned short, unsigned short>;
	using sea_cucumbers = std::set<sea_cucumber>;
	using size = sea_cucumber;

	friend std::istream& operator>>( std::istream& aInput, CSeaFloor& aSeaFloor );

	const sea_cucumbers& GetEastSeaCucumbers() const;
	const sea_cucumbers& GetSouthSeaCucumbers() const;
	const size& GetSize() const;
	const std::size_t& GetSteps() const;

	const std::size_t& MoveUntilStalled();
	sea_cucumbers MoveEast() const;
	sea_cucumbers MoveSouth() const;

private:
	sea_cucumbers mEastSeaCucumbers;
	sea_cucumbers mSouthSeaCucumbers;
	size mSize;
	std::size_t mSteps = 0;
};

#endif // C_SEA_FLOOR_H