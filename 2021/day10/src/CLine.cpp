#include "CLine.h"

#include <list>

namespace
{

bool IsOpening( const char& aSymbol );
bool AreMatching( const char& aOpeningSymbol, const char& aClosingSymbol );

}

std::istream& operator>>( std::istream& aInput, CLine& aDisplay )
{
	aInput >> aDisplay.mLine;
	return aInput;
}

const CLine::score_map& CLine::GET_SCORE_MAP()
{
	static score_map RESULT{
			{ ')', static_cast< unsigned short >( 3 ) },
			{ ']', static_cast< unsigned short >( 57 ) },
			{ '}', static_cast< unsigned short >( 1197 ) },
			{ '>', static_cast< unsigned short >( 25137 ) } };
	return RESULT;
}

const CLine::score_map& CLine::GET_COMPLETION_SCORE_MAP()
{
	static score_map RESULT{
			{ '(', static_cast< unsigned short >( 1 ) },
			{ '[', static_cast< unsigned short >( 2 ) },
			{ '{', static_cast< unsigned short >( 3 ) },
			{ '<', static_cast< unsigned short >( 4 ) } };
	return RESULT;
}

const std::string& CLine::GetLine() const
{
	return mLine;
}

size_t CLine::CalculateSyntaxErrorScore() const
{
	std::list<char> openings;
	for( const auto& symbol : mLine )
	{
		if( IsOpening( symbol ) )
			openings.emplace_back( symbol );
		else if( !openings.empty() && AreMatching( openings.back(), symbol ) )
			openings.pop_back();
		else
			return GET_SCORE_MAP().at( symbol );
	}
	return 0;
}

size_t CLine::CalculateCompletionScore() const
{
	size_t result = 0;

	std::list<char> openings;
	for( const auto& symbol : mLine )
	{
		if( IsOpening( symbol ) )
			openings.emplace_back( symbol );
		else
			openings.pop_back();
	}

	for( auto openingIt = openings.crbegin(); openingIt != openings.crend(); ++openingIt )
		result = result * 5 + static_cast< size_t >( GET_COMPLETION_SCORE_MAP().at( *openingIt ) );

	return result;
}

bool CLine::IsIncomplete() const
{
	return CalculateSyntaxErrorScore() == 0;
}

namespace
{

bool IsOpening( const char& aSymbol )
{
	return aSymbol == '(' || aSymbol == '[' || aSymbol == '{' || aSymbol == '<';
}

bool AreMatching( const char& aOpeningSymbol, const char& aClosingSymbol )
{
	return ( aOpeningSymbol == '(' && aClosingSymbol == ')' ) ||
		( aOpeningSymbol == '[' && aClosingSymbol == ']' ) ||
		( aOpeningSymbol == '{' && aClosingSymbol == '}' ) ||
		( aOpeningSymbol == '<' && aClosingSymbol == '>' );
}

}
