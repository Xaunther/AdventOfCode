#ifndef C_BURROW_H
#define C_BURROW_H

#include <istream>
#include <vector>

using CBurrow = std::vector<std::vector<bool>>;

std::istream& operator>>( std::istream& aInput, CBurrow& aBurrow );

#endif // C_BURROW_H