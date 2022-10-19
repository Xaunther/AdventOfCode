#include "CDeterministicDie.h"

CDeterministicDie::CDeterministicDie():
	ADie()
{
}

CDeterministicDie::rolls CDeterministicDie::DoRoll() const
{
	unsigned short result = mRollCount % 100;
	return result == 0 ? rolls{ { static_cast< unsigned short >( 100 ), 1 } } : rolls{ { result, 1 } };
}