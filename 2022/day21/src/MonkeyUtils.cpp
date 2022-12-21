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

long long CalculateHumanNumber( std::list<CMonkey>& aMonkeys, const CMonkey::id& aCheckerID, const CMonkey::id& aHumanID )
{
	std::map<CMonkey::id, long long> result;

	// Initial setup
	for( auto monkeyIt = aMonkeys.begin(); monkeyIt != aMonkeys.end(); )
	{
		if( ( *monkeyIt ).GetNumber() && ( *monkeyIt ).GetID() != aHumanID )
		{
			result.emplace( ( *monkeyIt ).GetID(), *( *monkeyIt ).GetNumber() );
			monkeyIt = aMonkeys.erase( monkeyIt );
		}
		else
			++monkeyIt;
	}

	std::size_t previousSize;
	do
	{
		previousSize = result.size();
		for( auto monkeyIt = aMonkeys.begin(); monkeyIt != aMonkeys.end(); )
		{
			if( ( *monkeyIt ).GetID() == aHumanID || ( *monkeyIt ).GetID() == aCheckerID )
			{
				++monkeyIt;
				continue;
			}
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
	} while( previousSize < result.size() );

	// Retrieve targetScore and targetID
	long long targetScore;
	CMonkey::id targetID;
	{
		const auto& checkerMonkey = *std::ranges::find_if( aMonkeys, [ &aCheckerID ]( auto&& aMonkey ) { return aMonkey.GetID() == aCheckerID; } );
		auto found = result.find( ( *checkerMonkey.GetOperands() ).first );
		if( found != result.cend() )
		{
			targetScore = ( *found ).second;
			targetID = ( *checkerMonkey.GetOperands() ).second;
		}
		else
		{
			targetScore = result[ ( *checkerMonkey.GetOperands() ).second ];
			targetID = ( *checkerMonkey.GetOperands() ).first;
		}
	}

	while( targetID != aHumanID )
	{
		const auto& foundMonkey = *std::ranges::find_if( aMonkeys, [ &targetID ]( auto&& aMonkey ) { return aMonkey.GetID() == targetID; } );
		switch( *foundMonkey.GetOperation() )
		{
		case CMonkey::EOperation::PLUS:
		{
			auto found = result.find( ( *foundMonkey.GetOperands() ).first );
			if( found != result.cend() )
			{
				targetScore = targetScore - ( *found ).second;
				targetID = ( *foundMonkey.GetOperands() ).second;
			}
			else
			{
				targetScore = targetScore - result[ ( *foundMonkey.GetOperands() ).second ];
				targetID = ( *foundMonkey.GetOperands() ).first;
			}
			break;
		}
		case CMonkey::EOperation::MINUS:
		{
			auto found = result.find( ( *foundMonkey.GetOperands() ).first );
			if( found != result.cend() )
			{
				targetScore = ( *found ).second - targetScore;
				targetID = ( *foundMonkey.GetOperands() ).second;
			}
			else
			{
				targetScore = targetScore + result[ ( *foundMonkey.GetOperands() ).second ];
				targetID = ( *foundMonkey.GetOperands() ).first;
			}
			break;
		}
		case CMonkey::EOperation::PROD:
		{
			auto found = result.find( ( *foundMonkey.GetOperands() ).first );
			if( found != result.cend() )
			{
				targetScore = targetScore / ( *found ).second;
				targetID = ( *foundMonkey.GetOperands() ).second;
			}
			else
			{
				targetScore = targetScore / result[ ( *foundMonkey.GetOperands() ).second ];
				targetID = ( *foundMonkey.GetOperands() ).first;
			}
			break;
		}
		default:
		{
			auto found = result.find( ( *foundMonkey.GetOperands() ).first );
			if( found != result.cend() )
			{
				targetScore = ( *found ).second / targetScore;
				targetID = ( *foundMonkey.GetOperands() ).second;
			}
			else
			{
				targetScore = targetScore * result[ ( *foundMonkey.GetOperands() ).second ];
				targetID = ( *foundMonkey.GetOperands() ).first;
			}
			break;
		}
		}
	}

	return targetScore;
}