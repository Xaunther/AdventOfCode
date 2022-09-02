#ifndef C_SUBMARINE_POSITION_H
#define C_SUBMARINE_POSITION_H

#include <utility>

class CMovement;

class CSubmarinePosition
{
public:
	using position = std::pair<int, int>;

	CSubmarinePosition();

	const position& GetPosition() const;
	const int& GetAim() const;

	void Move( const CMovement& aMovement );
	void MoveWithAim( const CMovement& aMovement );


private:
	position mPosition;
	int mAim;
};

#endif // C_SUBMARINE_POSITION_H