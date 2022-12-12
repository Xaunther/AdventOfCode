#pragma once

#include <iostream>

class CElevationMap
{
public:
	friend std::istream& operator>>( std::istream& aInput, CElevationMap& aElevationMap );

	std::string_view GetElevation() const;
	const unsigned int& GetWidth() const;
	const unsigned int& GetInitialPosition() const;
	const unsigned int& GetEndPosition() const;

private:
	std::string mElevation;
	unsigned int mWidth;
	unsigned int mInitialPosition;
	unsigned int mEndPosition;
};