#include "COperation.h"

#include <string>

namespace
{

std::istream& operator>>( std::istream& aInput, COperation::operand& aOperand );
std::istream& operator>>( std::istream& aInput, COperation::EOperator& aOperator );

}

std::istream& operator>>( std::istream& aInput, COperation& aOperation )
{
	std::string inputString;
	return aInput >> inputString >> inputString >> aOperation.mOperands.first >> aOperation.mOperator >> aOperation.mOperands.second;
}

std::size_t COperation::operator()( std::size_t& aOld ) const
{
	return mOperator == EOperator::SUM ? mOperands.first.value_or( aOld ) + mOperands.second.value_or( aOld ) : mOperands.first.value_or( aOld ) * mOperands.second.value_or( aOld );
}

namespace
{

std::istream& operator>>( std::istream& aInput, COperation::operand& aOperand )
{
	std::string inputString;
	aInput >> inputString;
	if( inputString == "old" )
		aOperand.reset();
	else
		aOperand = static_cast< unsigned int >( std::stoi( inputString ) );
	return aInput;
}

std::istream& operator>>( std::istream& aInput, COperation::EOperator& aOperator )
{
	std::string inputString;
	aInput >> inputString;
	if( inputString == "*" )
		aOperator = COperation::EOperator::MULT;
	else
		aOperator = COperation::EOperator::SUM;
	return aInput;
}

}