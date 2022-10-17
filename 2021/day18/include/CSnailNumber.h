#ifndef C_SNAIL_NUMBER_H
#define C_SNAIL_NUMBER_H

#include <istream>
#include <list>

class CSnailNumber
{
public:
	using value = std::size_t;
	using depth = unsigned short;
	using component = std::pair<value, depth>;
	using components = std::list<component>;

	friend std::istream& operator>>( std::istream& aInput, CSnailNumber& aSnailNumber );

	CSnailNumber& operator+=( const CSnailNumber& aRHS );

	const components& GetComponents() const;

	std::size_t Magnitude() const;

private:
	void Reduce();
	bool Explode();
	bool Split();

	components mComponents;

};

#endif // C_SNAIL_NUMBER_H