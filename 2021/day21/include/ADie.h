#ifndef A_DIE_H
#define A_DIE_H

#include <cstdlib>
#include <map>

class ADie
{
public:
	using rolls = std::map<unsigned short, std::size_t>;

	explicit ADie();
	virtual ~ADie() = 0;

	const std::size_t& GetRollCount();

	rolls Roll();

protected:
	virtual rolls DoRoll() const = 0;

	std::size_t mRollCount;
};

#endif // A_DIE_H