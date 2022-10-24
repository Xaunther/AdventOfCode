#ifndef C_INSTRUCTION_H
#define C_INSTRUCTION_H

#include <istream>
#include <optional>
#include <variant>

#include "CAlu.h"

class CInstruction
{
public:
	using argument = std::variant<CAlu::NUMBER, int>;
	using arguments = std::pair<CAlu::NUMBER, std::optional<argument>>;

	friend std::istream& operator>>( std::istream& aInput, CInstruction& aInstruction );

	enum class TYPE
	{
		INP,
		ADD,
		MUL,
		DIV,
		MOD,
		EQL
	};

	const TYPE& GetType() const;
	const arguments& GetArguments() const;

private:
	TYPE mType;
	arguments mArguments;
};

#endif // C_INSTRUCTION_H