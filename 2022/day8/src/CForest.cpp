#include "CForest.h"

#include <ranges>

namespace
{

std::set<CForest::tree_position> FindVisibleTreesInRow( const CForest::trees& aTrees, const CForest::tree_position::first_type& aRowIndex );
std::set<CForest::tree_position> FindVisibleTreesInCol( const CForest::trees& aTrees, const CForest::tree_position::second_type& aColIndex );

}

std::istream& operator>>( std::istream& aInput, CForest& aForest )
{
	for( const auto& inputLine : std::ranges::istream_view<std::string>( aInput ) )
	{
		CForest::trees::value_type treeRow;
		for( const auto& treeHeight : inputLine )
			treeRow.push_back( treeHeight - '0' );
		aForest.mTrees.push_back( std::move( treeRow ) );
	}
	return aInput;
}

const  CForest::trees& CForest::GetTrees() const
{
	return mTrees;
}

unsigned int CForest::CountVisibleTrees() const
{
	std::set<tree_position> result;
	for( tree_position::first_type rowIndex = 0; rowIndex < mTrees.size(); ++rowIndex )
		for( auto& visibleTreePosition : FindVisibleTreesInRow( mTrees, rowIndex ) )
			result.insert( std::move( visibleTreePosition ) );

	for( tree_position::second_type colIndex = 0; colIndex < mTrees.front().size(); ++colIndex )
		for( auto& visibleTreePosition : FindVisibleTreesInCol( mTrees, colIndex ) )
			result.insert( std::move( visibleTreePosition ) );

	return static_cast< unsigned int >( result.size() );
}

unsigned int CForest::HighestScenicScore() const
{
	unsigned int result = 0;

	for( tree_position::first_type rowIndex = 1; rowIndex < mTrees.size() - 1; ++rowIndex )
		for( tree_position::second_type colIndex = 1; colIndex < mTrees[ rowIndex ].size() - 1; ++colIndex )
			result = std::max( result, ScenicScore( rowIndex, colIndex ) );

	return result;
}

unsigned int CForest::ScenicScore( const tree_position::first_type& aRowIndex, const tree_position::second_type& aColIndex ) const
{
	if( aRowIndex == 0 || aColIndex == 0 || aRowIndex == mTrees.size() - 1 || aColIndex == mTrees[ aRowIndex ].size() - 1 )
		return 0;
	unsigned int result = 1;
	//UP
	{
		unsigned int count = 1;
		for( tree_position::first_type rowIndex = aRowIndex - 1; rowIndex > 0 && mTrees[ rowIndex ][ aColIndex ] < mTrees[ aRowIndex ][ aColIndex ];--rowIndex, ++count );
		result *= count;
	}
	//DOWN
	{
		unsigned int count = 1;
		for( tree_position::first_type rowIndex = aRowIndex + 1; rowIndex < mTrees.size() - 1 && mTrees[ rowIndex ][ aColIndex ] < mTrees[ aRowIndex ][ aColIndex ];++rowIndex, ++count );
		result *= count;
	}
	//LEFT
	{
		unsigned int count = 1;
		for( tree_position::second_type colIndex = aColIndex - 1; colIndex > 0 && mTrees[ aRowIndex ][ colIndex ] < mTrees[ aRowIndex ][ aColIndex ];--colIndex, ++count );
		result *= count;
	}
	//RIGHT
	{
		unsigned int count = 1;
		for( tree_position::second_type colIndex = aColIndex + 1; colIndex < mTrees[ aRowIndex ].size() - 1 && mTrees[ aRowIndex ][ colIndex ] < mTrees[ aRowIndex ][ aColIndex ];++colIndex, ++count );
		result *= count;
	}
	return result;
}

namespace
{

std::set<CForest::tree_position> FindVisibleTreesInRow( const CForest::trees& aTrees, const CForest::tree_position::first_type& aRowIndex )
{
	std::set<CForest::tree_position> result;

	{
		result.emplace( aRowIndex, CForest::tree_position::second_type{ 0 } );
		auto highest = aTrees[ aRowIndex ][ 0 ];
		for( CForest::tree_position::second_type colIndex = 1; colIndex < aTrees[ aRowIndex ].size() - 1; ++colIndex )
		{
			if( aTrees[ aRowIndex ][ colIndex ] > highest )
			{
				highest = aTrees[ aRowIndex ][ colIndex ];
				result.emplace( aRowIndex, colIndex );
			}
		}
	}

	{
		result.emplace( aRowIndex, static_cast< CForest::tree_position::second_type >( aTrees[ aRowIndex ].size() - 1 ) );
		auto highest = aTrees[ aRowIndex ][ aTrees[ aRowIndex ].size() - 1 ];
		for( CForest::tree_position::second_type colIndex = static_cast< CForest::tree_position::second_type > ( aTrees[ aRowIndex ].size() - 2 ); colIndex > 0; --colIndex )
		{
			if( aTrees[ aRowIndex ][ colIndex ] > highest )
			{
				highest = aTrees[ aRowIndex ][ colIndex ];
				result.emplace( aRowIndex, colIndex );
			}
		}
	}

	return result;
}

std::set<CForest::tree_position> FindVisibleTreesInCol( const CForest::trees& aTrees, const CForest::tree_position::second_type& aColIndex )
{
	std::set<CForest::tree_position> result;

	{
		result.emplace( CForest::tree_position::first_type{ 0 }, aColIndex );
		auto highest = aTrees[ 0 ][ aColIndex ];
		for( CForest::tree_position::first_type rowIndex = 1; rowIndex < aTrees.size() - 1; ++rowIndex )
		{
			if( aTrees[ rowIndex ][ aColIndex ] > highest )
			{
				highest = aTrees[ rowIndex ][ aColIndex ];
				result.emplace( rowIndex, aColIndex );
			}
		}
	}

	{
		result.emplace( static_cast< CForest::tree_position::first_type >( aTrees.size() - 1 ), aColIndex );
		auto highest = aTrees[ aTrees.size() - 1 ][ aColIndex ];
		for( CForest::tree_position::first_type rowIndex = static_cast< CForest::tree_position::first_type >( aTrees.size() - 2 ); rowIndex > 0; --rowIndex )
		{
			if( aTrees[ rowIndex ][ aColIndex ] > highest )
			{
				highest = aTrees[ rowIndex ][ aColIndex ];
				result.emplace( rowIndex, aColIndex );
			}
		}
	}

	return result;
}

}