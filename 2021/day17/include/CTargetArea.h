#ifndef C_TARGET_AREA_H
#define C_TARGET_AREA_H

#include <istream>

class CProjectile;

class CTargetArea
{
public:
	using range = std::pair<int, int>;

	friend std::istream& operator>>( std::istream& aInput, CTargetArea& aTargetArea );

	const range& GetRangeX() const;
	const range& GetRangeY() const;

	bool IsInside( const CProjectile& aProjectile ) const;

private:
	range mRangeX;
	range mRangeY;
};

#endif // C_TARGET_AREA_H