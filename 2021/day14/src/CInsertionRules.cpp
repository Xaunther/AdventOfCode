#include "CInsertionRules.h"

std::istream& operator>>( std::istream& aInput, CInsertionRules& aInsertionRules )
{
	while( aInput )
	{
		std::string insertionKey;
		std::string basura;
		char insertionValue;
		std::string insertionKeyEnd;
		aInput >> insertionKey;
		if( insertionKey.empty() )
			break;
		aInput >> basura;
		aInput >> insertionValue;
		insertionKeyEnd = insertionKey;
		insertionKeyEnd.insert( insertionKeyEnd.begin() + 1, insertionValue );
		aInsertionRules.mInsertionRules.emplace( insertionKey, std::make_pair( insertionKeyEnd.substr( 0, 2 ), insertionKeyEnd.substr( 1, 2 ) ) );
	}
	return aInput;
}

const CInsertionRules::insertion_rules& CInsertionRules::GetInsertionRules() const
{
	return mInsertionRules;
}
