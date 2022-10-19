#include "CDiracDie.h"

CDiracDie::CDiracDie():
	ADie()
{
}

CDiracDie::rolls CDiracDie::DoRoll() const
{
	return { { unsigned short{ 1 }, 1 }, { unsigned short{ 2 }, 1 }, { unsigned short{ 3 }, 1 } };
}