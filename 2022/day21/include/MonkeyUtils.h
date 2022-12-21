#pragma once

#include <list>

#include "CMonkey.h"

long long CalculateMonkeyNumber( std::list<CMonkey>& aMonkeys, const CMonkey::id& aMonkeyID );
long long CalculateHumanNumber( std::list<CMonkey>& aMonkeys, const CMonkey::id& aCheckerID, const CMonkey::id& aHumanID );