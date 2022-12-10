#include "CInstruction.h"

namespace
{

std::istream& operator>>( std::istream& aInput, CInstruction::EType& aDirection );

}

std::istream& operator>>( std::istream& aInput, CInstruction& aInstruction )
{
	aInput >> aInstruction.mType;
	if( aInstruction.mType == CInstruction::EType::ADDX )
		aInput >> aInstruction.mValue;
	else
		aInstruction.mValue = 0;
	return aInput;
}

const CInstruction::EType& CInstruction::GetType() const
{
	return mType;
}

const int& CInstruction::GetValue() const
{
	return mValue;
}

namespace
{

std::istream& operator>>( std::istream& aInput, CInstruction::EType& aDirection )
{
	std::string inputString;
	aInput >> inputString;

	if( inputString == "noop" )
		aDirection = CInstruction::EType::NOOP;
	else
		aDirection = CInstruction::EType::ADDX;

	return aInput;
}

}