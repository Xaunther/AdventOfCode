#include "CCubeRotations.h"

namespace
{

rotation_matrix operator*( const rotation_matrix& aLHS, const rotation_matrix& aRHS );
rotation_matrix Transpose( const rotation_matrix& aRotationMatrix );

}

const cube_rotations& GenerateCubeRotations()
{
	static cube_rotations result;

	result[ 0 ] = rotation_matrix{
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{0,0,1}
	};
	result[ 1 ] = rotation_matrix{
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{0,1,0}
	};
	result[ 2 ] = rotation_matrix{
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{0,0,-1}
	};
	result[ 3 ] = rotation_matrix{
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{0,-1,0}
	};
	result[ 4 ] = rotation_matrix{
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,0,1}
	};
	result[ 5 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,1,0}
	};
	result[ 6 ] = rotation_matrix{
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,0,-1}
	};
	result[ 7 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{1,0,0},
		rotation_matrix::value_type{0,-1,0}
	};
	result[ 8 ] = rotation_matrix{
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{0,0,1}
	};
	result[ 9 ] = rotation_matrix{
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{0,-1,0}
	};
	result[ 10 ] = rotation_matrix{
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{0,0,-1}
	};
	result[ 11 ] = rotation_matrix{
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{0,1,0}
	};
	result[ 12 ] = rotation_matrix{
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,0,1}
	};
	result[ 13 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,-1,0}
	};
	result[ 14 ] = rotation_matrix{
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,0,-1}
	};
	result[ 15 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{-1,0,0},
		rotation_matrix::value_type{0,1,0}
	};
	result[ 16 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{1,0,0}
	};
	result[ 17 ] = rotation_matrix{
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{1,0,0}
	};
	result[ 18 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{1,0,0}
	};
	result[ 19 ] = rotation_matrix{
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{1,0,0}
	};
	result[ 20 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{-1,0,0}
	};
	result[ 21 ] = rotation_matrix{
		rotation_matrix::value_type{0,-1,0},
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{-1,0,0}
	};
	result[ 22 ] = rotation_matrix{
		rotation_matrix::value_type{0,0,1},
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{-1,0,0}
	};
	result[ 23 ] = rotation_matrix{
		rotation_matrix::value_type{0,1,0},
		rotation_matrix::value_type{0,0,-1},
		rotation_matrix::value_type{-1,0,0}
	};

	return result;
}

std::size_t ComposeRotationIndexes( const std::size_t& aFirstRotationIndex, const std::size_t& aSecondRotationIndex )
{
	const auto& rotationMatrices = GenerateCubeRotations();
	const auto& rotation = rotationMatrices[ aSecondRotationIndex ] * rotationMatrices[ aFirstRotationIndex ];
	const auto& found = std::find( rotationMatrices.cbegin(), rotationMatrices.cend(), rotation );
	return static_cast< std::size_t >( std::distance( rotationMatrices.cbegin(), found ) );
}

std::size_t InverseRotationIndex( const std::size_t& aRotationIndex )
{
	const auto& rotationMatrices = GenerateCubeRotations();
	const auto& inverseRotationMatrix = Transpose( rotationMatrices[ aRotationIndex ] );
	const auto& found = std::find( rotationMatrices.cbegin(), rotationMatrices.cend(), inverseRotationMatrix );
	return static_cast< std::size_t >( std::distance( rotationMatrices.cbegin(), found ) );
}

namespace
{

rotation_matrix operator*( const rotation_matrix& aLHS, const rotation_matrix& aRHS )
{
	rotation_matrix result;

	for( std::size_t i = 0; i < aLHS.size(); ++i )
		for( std::size_t j = 0; j < aLHS.size(); ++j )
		{
			result[ i ][ j ] = 0;
			for( std::size_t k = 0; k < aLHS.size(); ++k )
				result[ i ][ j ] += aLHS[ i ][ k ] * aRHS[ k ][ j ];
		}
	return result;
}

rotation_matrix Transpose( const rotation_matrix& aRotationMatrix )
{
	rotation_matrix result;
	for( std::size_t i = 0; i < aRotationMatrix.size(); ++i )
		for( std::size_t j = 0; j < aRotationMatrix.size(); ++j )
			result[ i ][ j ] = aRotationMatrix[ j ][ i ];
	return result;
}

}