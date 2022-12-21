#include "CMonkey.h"

#include <string>

std::istream& operator>>( std::istream& aInput, CMonkey& aMonkey )
{
	aMonkey.Reset();
	std::string word;
	aInput >> word;
	aMonkey.mID = word.substr( 0, word.size() - 1 );
	aInput >> word;
	if( std::isdigit( word.front() ) )
		aMonkey.mNumber = std::stoi( word );
	else
	{
		aMonkey.mOperands.emplace( word, "" );
		aInput >> word;
		if( word == "+" )
			aMonkey.mOperation = CMonkey::EOperation::PLUS;
		else if( word == "-" )
			aMonkey.mOperation = CMonkey::EOperation::MINUS;
		else if( word == "*" )
			aMonkey.mOperation = CMonkey::EOperation::PROD;
		else
			aMonkey.mOperation = CMonkey::EOperation::DIV;
		aInput >> ( *aMonkey.mOperands ).second;
	}
	return aInput;
}

const CMonkey::id& CMonkey::GetID() const
{
	return mID;
}

const CMonkey::optional_number& CMonkey::GetNumber() const
{
	return mNumber;
}

const CMonkey::optional_operation& CMonkey::GetOperation() const
{
	return mOperation;
}

const CMonkey::optional_operands& CMonkey::GetOperands() const
{
	return mOperands;
}

void CMonkey::Reset()
{
	CMonkey tmp;
	std::swap( *this, tmp );
}