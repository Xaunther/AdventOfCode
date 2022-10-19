#ifndef C_DIRAC_DIE_H
#define C_DIRAC_DIE_H

#include "ADie.h"

class CDiracDie: public ADie
{
public:
	explicit CDiracDie();

private:
	rolls DoRoll() const override;
};

#endif // C_DIRAC_DIE