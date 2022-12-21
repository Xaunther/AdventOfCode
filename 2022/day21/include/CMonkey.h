#pragma once

#include <istream>
#include <optional>

class CMonkey
{
public:
	enum class EOperation
	{
		PLUS,
		MINUS,
		PROD,
		DIV
	};

	using id = std::string;
	using optional_number = std::optional<long long>;
	using optional_operation = std::optional<EOperation>;
	using optional_operands = std::optional<std::pair<id, id>>;

	friend std::istream& operator>>( std::istream& aInput, CMonkey& aMonkey );

	const id& GetID() const;
	const optional_number& GetNumber() const;
	const optional_operation& GetOperation() const;
	const optional_operands& GetOperands() const;

	void Reset();

private:
	id mID;
	optional_number mNumber;
	optional_operation mOperation;
	optional_operands mOperands;
};