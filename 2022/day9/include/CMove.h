#pragma once

#include <istream>

class CMove
{
public:
	enum class EDirection
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	friend std::istream& operator>>( std::istream& aInput, CMove& aMove );

	const EDirection& GetDirection() const;
	const unsigned short& GetDistance() const;

private:
	EDirection mDirection;
	unsigned short mDistance;
};