#ifndef C_DETERMINISTIC_DIE_H
#define C_DETERMINISTIC_DIE_H

#include "ADie.h"

class CDeterministicDie: public ADie
{
public:
	explicit CDeterministicDie();

private:
	rolls DoRoll() const override;
};

#endif // C_DETERMINISTIC_DIE_H