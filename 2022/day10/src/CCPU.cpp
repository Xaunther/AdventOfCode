#include "CCPU.h"

#include "CInstruction.h"

const CCPU::cycles& CCPU::GetCycles() const
{
	return mCycles;
}

void CCPU::PerformInstruction( const CInstruction& aInstruction )
{
	AddValue( 0 );
	if( aInstruction.GetType() == CInstruction::EType::ADDX )
		AddValue( aInstruction.GetValue() );
}

long CCPU::SignalStrength( const unsigned int& aCycleNumber )
{
	return mCycles[ aCycleNumber - 1 ] * aCycleNumber;
}


void CCPU::AddValue( const int& aValue )
{
	mCycles.emplace_back( mCycles.back() + aValue );
}