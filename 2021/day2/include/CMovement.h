#ifndef C_MOVEMENT_H
#define C_MOVEMENT_H

#include <string>
#include <iostream>

class CMovement
{
public:
	CMovement();

	friend std::istream& operator>>( std::istream& aInput, CMovement& aMovement );

	const std::string& GetDirection() const;
	const unsigned int& GetDistance() const;

private:
	std::string mDirection;
	unsigned int mDistance;
};

#endif // C_SUBMARINE_POSITION_H