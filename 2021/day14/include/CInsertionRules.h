#ifndef C_INSERTION_RULES_H
#define C_INSERTION_RULES_H

#include <istream>
#include <map>

class CInsertionRules
{
public:
	using insertion_rules = std::map<std::string, std::pair<std::string, std::string>>;

	friend std::istream& operator>>( std::istream& aInput, CInsertionRules& aInsertionRules );

	const insertion_rules& GetInsertionRules() const;

private:
	insertion_rules mInsertionRules;
};

#endif // C_INSERTION_RULES_H