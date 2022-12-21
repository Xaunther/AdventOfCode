#include "MonkeyUtils.h"

#include <iostream>
#include <map>

long long CalculateMonkeyNumber( std::list<CMonkey>& aMonkeys, const CMonkey::id& aMonkeyID )
{
	std::map<CMonkey::id, long long> result;

	// Initial setup
	for( auto monkeyIt = aMonkeys.begin(); monkeyIt != aMonkeys.end(); )
	{
		if( ( *monkeyIt ).GetNumber() )
		{
			result.emplace( ( *monkeyIt ).GetID(), *( *monkeyIt ).GetNumber() );
			monkeyIt = aMonkeys.erase( monkeyIt );
		}
		else
			++monkeyIt;
	}

	auto foundResult = result.cbegin();
	while( ( foundResult = result.find( aMonkeyID ) ) == result.cend() )
	{
		for( auto monkeyIt = aMonkeys.begin(); monkeyIt != aMonkeys.end(); )
		{
			auto itLHS = result.find( ( *( *monkeyIt ).GetOperands() ).first );
			if( itLHS == result.cend() )
			{
				++monkeyIt;
				continue;
			}
			auto itRHS = result.find( ( *( *monkeyIt ).GetOperands() ).second );
			if( itRHS == result.cend() )
			{
				++monkeyIt;
				continue;
			}
			long long operationResult;
			switch( *( *monkeyIt ).GetOperation() )
			{
			case CMonkey::EOperation::PLUS: operationResult = ( *itLHS ).second + ( *itRHS ).second; break;
			case CMonkey::EOperation::MINUS: operationResult = ( *itLHS ).second - ( *itRHS ).second; break;
			case CMonkey::EOperation::PROD: operationResult = ( *itLHS ).second * ( *itRHS ).second; break;
			default: operationResult = ( *itLHS ).second / ( *itRHS ).second; break;
			}
			result.emplace( ( *monkeyIt ).GetID(), operationResult );
			monkeyIt = aMonkeys.erase( monkeyIt );
		}
	}

	return ( *foundResult ).second;
}
