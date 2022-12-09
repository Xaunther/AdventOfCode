#include "CRopePosition.h"

namespace
{

std::pair<bool, bool> AreAdjacent( const CRopePosition::position& aLHS, const CRopePosition::position& aRHS );
bool AreAdjacent( const int aLHS, const int aRHS );

}

CRopePosition::CRopePosition( const unsigned int& aKnotNumber ):
	mKnotPositions( aKnotNumber, { 0, 0 } )
{
}

const CRopePosition::positions& CRopePosition::GetPositions() const
{
	return mKnotPositions;
}

const CRopePosition::position_history& CRopePosition::GetTailHistory() const
{
	return mTailHistory;
}

void CRopePosition::Move( const CMove& aMove )
{
	for( unsigned short moveNumber = 0; moveNumber < aMove.GetDistance(); ++moveNumber )
	{
		MoveHead( aMove.GetDirection() );
		AdjustTailPositions();
	}
}

void CRopePosition::MoveHead( const CMove::EDirection& aDirection )
{
	switch( aDirection )
	{
	case CMove::EDirection::LEFT: --mKnotPositions.front().first; break;
	case CMove::EDirection::RIGHT: ++mKnotPositions.front().first; break;
	case CMove::EDirection::UP: ++mKnotPositions.front().second; break;
	case CMove::EDirection::DOWN: --mKnotPositions.front().second; break;
	}
}

void CRopePosition::AdjustTailPositions()
{
	for( auto tailIt = mKnotPositions.begin() + 1; tailIt != mKnotPositions.end(); ++tailIt )
	{
		const auto& headPosition = *( tailIt - 1 );
		auto& tailPosition = *tailIt;
		const auto& areAdjacent = AreAdjacent( headPosition, tailPosition );
		// Diagonal moves
		if( ( !areAdjacent.first || !areAdjacent.second ) && headPosition.first != tailPosition.first && headPosition.second != tailPosition.second )
		{
			if( headPosition.first > tailPosition.first )
				++tailPosition.first;
			else
				--tailPosition.first;
			if( headPosition.second > tailPosition.second )
				++tailPosition.second;
			else
				--tailPosition.second;
		}
		else if( !areAdjacent.first )
		{
			if( headPosition.first > tailPosition.first )
				++tailPosition.first;
			else
				--tailPosition.first;
		}
		else if( !areAdjacent.second )
		{
			if( headPosition.second > tailPosition.second )
				++tailPosition.second;
			else
				--tailPosition.second;
		}
	}
	mTailHistory.insert( mKnotPositions.back() );
}

namespace
{

std::pair<bool, bool> AreAdjacent( const CRopePosition::position& aLHS, const CRopePosition::position& aRHS )
{
	return { AreAdjacent( aLHS.first, aRHS.first ), AreAdjacent( aLHS.second, aRHS.second ) };
}

bool AreAdjacent( const int aLHS, const int aRHS )
{
	return aLHS - 1 <= aRHS && aLHS + 1 >= aRHS;
}

}