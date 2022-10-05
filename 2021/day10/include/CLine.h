#ifndef C_LINE_H
#define C_LINE_H

#include <istream>
#include <map>
#include <string>

class CLine
{
public:
	using score_map = std::map<char, unsigned short>;

	friend std::istream& operator>>( std::istream& aInput, CLine& aDisplay );

	const std::string& GetLine() const;

	size_t CalculateSyntaxErrorScore() const;
	size_t CalculateCompletionScore() const;

	bool IsIncomplete() const;

	static const score_map& GET_SCORE_MAP();
	static const score_map& GET_COMPLETION_SCORE_MAP();

private:
	std::string mLine;
};

#endif // C_LINE_H