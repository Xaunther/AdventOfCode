#ifndef C_BALLS_H
#define C_BALLS_H

#include <vector>
#include <iostream>

class CBalls
{
public:
	using balls = std::vector<unsigned int>;

	friend std::istream& operator>>( std::istream& aInput, CBalls& aBalls );

	const balls& GetBalls() const;

private:
	balls mBalls;
};

#endif // C_BALLS_H