#pragma once

#include <istream>
#include <set>
#include <vector>

class CForest
{
public:
	using trees = std::vector<std::vector<unsigned short>>;
	using tree_position = std::pair<unsigned short, unsigned short>;

	friend std::istream& operator>>( std::istream& aInput, CForest& aForest );

	const trees& GetTrees() const;

	unsigned int CountVisibleTrees() const;
	unsigned int HighestScenicScore() const;
	unsigned int ScenicScore( const tree_position::first_type& aRowIndex, const tree_position::second_type& aColIndex ) const;

private:
	trees mTrees;
};