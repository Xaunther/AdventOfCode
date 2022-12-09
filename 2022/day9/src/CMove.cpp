#include "CMove.h"

namespace
{

std::istream& operator>>( std::istream& aInput, CMove::EDirection& aDirection );

}

std::istream& operator>>( std::istream& aInput, CMove& aMove )
{
	return aInput >> aMove.mDirection >> aMove.mDistance;
}

const CMove::EDirection& CMove::GetDirection() const
{
	return mDirection;
}
const unsigned short& CMove::GetDistance() const
{
	return mDistance;
}

namespace
{

std::istream& operator>>( std::istream& aInput, CMove::EDirection& aDirection )
{
	char inputChar;
	aInput >> inputChar;

	switch( inputChar )
	{
	case 'L': aDirection = CMove::EDirection::LEFT; break;
	case 'R': aDirection = CMove::EDirection::RIGHT; break;
	case 'U': aDirection = CMove::EDirection::UP; break;
	default: aDirection = CMove::EDirection::DOWN; break;
	}

	return aInput;
}

}