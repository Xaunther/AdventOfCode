#ifndef C_TRAJECTORY_UTILS_H
#define C_TRAJECTORY_UTILS_H

#include "CTargetArea.h"

std::size_t MaxY( const CTargetArea::range& aRangeY );
std::size_t CountPossibleTrajectories( const CTargetArea& aTargetArea );

#endif // C_TRAJECTORY_UTILS_H