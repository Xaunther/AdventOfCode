#ifndef C_RISK_MAP_H
#define C_RISK_MAP_H

#include <istream>
#include <vector>

using risk = unsigned short;
using CRiskMap = std::vector<std::vector<risk>>;
std::istream& operator>>( std::istream& aInput, CRiskMap& aRiskMap );

#endif // C_RISK_MAP_H