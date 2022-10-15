#ifndef C_PROJECTILE_H
#define C_PROJECTILE_H

#include <utility>

class CProjectile
{
public:
	using position = std::pair<int, int>;
	using velocity = std::pair<int, int>;

	CProjectile( const velocity& aVelocity );

	const position GetPosition() const;
	const velocity GetVelocity() const;

	void Move();

private:
	position mPosition;
	velocity mVelocity;
};

#endif // C_PROJECTILE_H