#ifndef C_MODEL_NUMBER_H
#define C_MODEL_NUMBER_H

#include <ostream>
#include <vector>

using CModelNumber = std::vector<unsigned short>;

std::ostream& operator<<( std::ostream& aOutput, const CModelNumber& aModelNumber );

#endif // C_MODEL_NUMBER_H