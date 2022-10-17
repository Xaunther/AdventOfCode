#ifndef C_CUBE_ROTATIONS_H
#define C_CUBE_ROTATIONS_H

#include <array>

using rotation_matrix = std::array < std::array<int, 3>, 3 >;
using cube_rotations = std::array<rotation_matrix, 24>;

const cube_rotations& GenerateCubeRotations();
std::size_t ComposeRotationIndexes( const std::size_t& aFirstRotationIndex, const std::size_t& aSecondRotationIndex );
std::size_t InverseRotationIndex( const std::size_t& aRotationIndex );

#endif // C_CUBE_ROTATIONS_H