#include "ADie.h"

ADie::ADie():
	mRollCount( 0 )
{
}

ADie::~ADie()
{
}

const std::size_t& ADie::GetRollCount()
{
	return mRollCount;
}

ADie::rolls ADie::Roll()
{
	++mRollCount;
	return DoRoll();
}
