#include "CInstruction.h"

#include <string>

std::istream& operator>>( std::istream& aInput, CInstruction& aInstruction )
{
	std::string input;
	if( !( aInput >> input ) )
		return aInput;
	if( input == "inp" )
		aInstruction.mType = CInstruction::TYPE::INP;
	else if( input == "add" )
		aInstruction.mType = CInstruction::TYPE::ADD;
	else if( input == "mul" )
		aInstruction.mType = CInstruction::TYPE::MUL;
	else if( input == "div" )
		aInstruction.mType = CInstruction::TYPE::DIV;
	else if( input == "mod" )
		aInstruction.mType = CInstruction::TYPE::MOD;
	else if( input == "eql" )
		aInstruction.mType = CInstruction::TYPE::EQL;

	//First argument
	aInput >> input;
	if( input == "w" )
		aInstruction.mArguments.first = CAlu::NUMBER::W;
	else if( input == "x" )
		aInstruction.mArguments.first = CAlu::NUMBER::X;
	else if( input == "y" )
		aInstruction.mArguments.first = CAlu::NUMBER::Y;
	else
		aInstruction.mArguments.first = CAlu::NUMBER::Z;

	//Second argument
	if( aInstruction.mType != CInstruction::TYPE::INP )
	{
		aInput >> input;
		if( input == "w" )
			aInstruction.mArguments.second = CAlu::NUMBER::W;
		else if( input == "x" )
			aInstruction.mArguments.second = CAlu::NUMBER::X;
		else if( input == "y" )
			aInstruction.mArguments.second = CAlu::NUMBER::Y;
		else if( input == "z" )
			aInstruction.mArguments.second = CAlu::NUMBER::Z;
		else
			aInstruction.mArguments.second = std::stoi( input );
	}
	return aInput;
}

const CInstruction::TYPE& CInstruction::GetType() const
{
	return mType;
}

const CInstruction::arguments& CInstruction::GetArguments() const
{
	return mArguments;
}
