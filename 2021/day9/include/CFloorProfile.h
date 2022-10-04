#ifndef C_FLOOR_PROFILE_H
#define C_FLOOR_PROFILE_H

#include <vector>
#include <istream>

class CFloorProfile
{
public:
	using height_map = std::vector<std::vector<unsigned short>>;

	friend std::istream& operator>>( std::istream& aInput, CFloorProfile& aDisplay );

	const height_map& GetHeightMap() const;

	size_t CalculateRiskLevel() const;
	size_t CalculateBasinFactor() const;

private:
	height_map mHeightMap;
};

#endif // C_FLOOR_PROFILE_H