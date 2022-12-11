#pragma once

#include <istream>
#include <optional>

class COperation
{
public:
	using operand = std::optional<std::size_t>;
	using operands = std::pair<operand, operand>;
	enum class EOperator
	{
		SUM,
		MULT
	};

	friend std::istream& operator>>( std::istream& aInput, COperation& aOperation );
	std::size_t operator()( std::size_t& aOld ) const;

private:
	operands mOperands;
	EOperator mOperator;
};